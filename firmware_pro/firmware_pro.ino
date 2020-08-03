
#include "debug.h"
#include "sensor.h"
#include "config.h"
#include "led_blink.h"
#include "filter.h"
#include "artl/button.h"
#include "artl/digital_out.h"
#include "artl/digital_in.h"
#include "artl/timer.h"
#include "artl/yield.h"

enum { // milliseconds
    CANCEL_TIMEOUT = 15000, // 15 sec
};

enum {
    STATE_INTRO,
    STATE_NORMAL,
    STATE_CFG,
    STATE_CFG_CANCEL,
    STATE_CFG_SET_FULL,
    STATE_CFG_SET_LOW,
    STATE_CFG_STORE,
};

using b_empty = artl::digital_in<2>;
using b_full = artl::digital_in<4>;

artl::timer<> cancel_cfg_timer;
artl::timer<> read_sensor_timer;

uint8_t state = STATE_INTRO;

config_t cfg;

struct empty_btn_handler {
    void on_down(bool, unsigned long);
    void on_hold(unsigned long);
};

struct full_btn_handler {
    void on_down(bool, unsigned long);
    void on_hold(unsigned long);
};

artl::button<empty_btn_handler, 5, 2000> empty_btn;
artl::button<full_btn_handler, 5, 2000> full_btn;
filter_t sensor_filter;

void set_state(uint8_t s) {
    debug(2, "state ", s);

    state = s;
}

void setup() {
    unsigned long t = millis();

    Serial.begin(115200);

    sensor::setup();
    led_blink.setup();

    cfg.read();

    read_sensor_timer.schedule(t);

    set_state(STATE_INTRO);
    led_blink.start(led_blink_t::MODE_INTRO, t);

    artl::yield();
}

void start_cfg(unsigned long t) {
    debug(2, "start_cfg");

    set_state(STATE_CFG);

    cancel_cfg_timer.schedule(t + CANCEL_TIMEOUT);
    led_blink.start(led_blink_t::MODE_CFG_START, t);
}

void store_cfg(unsigned long t) {
    debug(2, "store_cfg");

    set_state(STATE_CFG_STORE);

    cancel_cfg_timer.cancel();

    uint8_t m = led_blink.get_mode() - led_blink_t::MODE_CFG_START;

    if (m < config_t::MAX_LED) {
        cfg.set(m, sensor_filter);
        led_blink.start(led_blink_t::MODE_SET_START + m, t);
    } else {
        cfg.reset();
        led_blink.start(led_blink_t::MODE_RESET, t);
    }
}

void cancel_cfg(unsigned long) {
    debug(2, "cancel_cfg");

    set_state(STATE_CFG_CANCEL);

    cfg.read();

    cancel_cfg_timer.cancel();
    led_blink.cancel();

    set_state(STATE_NORMAL);
}

void update_led(unsigned long sensor_val, unsigned long t) {
    if (!sensor::ready) {
        led_blink.start(led_blink_t::MODE_NO_SENSOR, t);
        return;
    }

    uint16_t v = cfg.led(sensor_val);
    if (v < 1) {
        led_blink.start(led_blink_t::MODE_EMPTY, t);
        return;
    }

    led_blink.set(led_blink.level2mask(v));
}

void check_sensor(unsigned long t) {
    if (read_sensor_timer.update(t)) {
        sensor::read(t);

        return;
    }

    if (sensor::update(t)) {
        read_sensor_timer.schedule(t + 500);

        unsigned long sv = sensor::value;

        if (empty_btn.down() || state == STATE_INTRO) {
            sv = sensor_filter.update(sv, 0);
        } else {
            sv = sensor_filter.update(sv, t);
        }

        debug(4, pwm::pulse_us, " ", pwm::low_us, " ",
            pwm::pulse_count, " ", sensor::value, " ", sv, " ",
            sensor_filter.mean_, " ", sensor_filter.cov_);

        if (state == STATE_NORMAL) {
            update_led(sv, t);
        }
    }
}

void loop() {
    unsigned long t = millis();

    check_sensor(t);

    if (led_blink.update(t)) {
        switch (state) {
        case STATE_INTRO:
            set_state(STATE_NORMAL);
            break;

        case STATE_CFG:
            led_blink.start(led_blink_t::MODE_CFG_START, t);
            break;

        case STATE_CFG_STORE:
            set_state(STATE_NORMAL);
            break;
        }
    }

    if (cancel_cfg_timer.update(t)) {
        cancel_cfg(t);
    }

    empty_btn.update(b_empty::read() == 0, t);
    full_btn.update(b_full::read() == 0, t);

    artl::yield();
}

void empty_btn_handler::on_down(bool down, unsigned long t) {
    if (down && state == STATE_CFG) {
        uint8_t m = led_blink.get_mode() - led_blink_t::MODE_CFG_START;
        const uint8_t cfg_count = led_blink_t::MODE_CFG_END - led_blink_t::MODE_CFG_START;
        m = (m + 1) % cfg_count;

        led_blink.start(led_blink_t::MODE_CFG_START + m, t);

        cancel_cfg_timer.schedule(t + CANCEL_TIMEOUT);
    }
}

void empty_btn_handler::on_hold(unsigned long t) {
    debug(2, "empty::hold");

    if (full_btn.hold() && state == STATE_NORMAL) {
        start_cfg(t);
    }
}

void full_btn_handler::on_down(bool down, unsigned long t) {
    if (down && state == STATE_CFG) {
        cancel_cfg_timer.schedule(t + CANCEL_TIMEOUT);
    }
}

void full_btn_handler::on_hold(unsigned long t) {
    debug(2, "full::hold");

    if (empty_btn.hold() && state == STATE_NORMAL) {
        start_cfg(t);
        return;
    }

    if (empty_btn.down()) { return; }

    if (state == STATE_CFG) {
        store_cfg(t);
    }
}
