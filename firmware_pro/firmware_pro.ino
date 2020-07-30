
#include "debug.h"
#include "sensor.h"
#include "config.h"
#include "led_blink.h"
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

using b_empty = artl::digital_in<4>;
using b_full = artl::digital_in<2>;

artl::timer<> cancel_cfg_timer;

uint8_t state = STATE_INTRO;

void set_state(uint8_t s) {
    debug(2, "state ", s);

    state = s;
}

void setup() {
    Serial.begin(115200);

    sensor::setup();
    led_blink.setup();

    set_state(STATE_INTRO);

    led_blink.start(led_blink_t::MODE_INTRO, millis());

    artl::yield();
}

unsigned long last_read_time = 0;
unsigned long last_update = 0;
int last_val = 0;
config_t cfg;

struct empty_btn_handler {
    void on_down(bool, unsigned long) { }
    void on_hold(unsigned long);
};

struct full_btn_handler {
    void on_down(bool, unsigned long) { }
    void on_hold(unsigned long);
};

artl::button<empty_btn_handler> empty_btn;
artl::button<full_btn_handler> full_btn;

void start_cfg(unsigned long t) {
    debug(2, "start_cfg");

    set_state(STATE_CFG);

    cancel_cfg_timer.schedule(t + CANCEL_TIMEOUT);
    led_blink.start(led_blink_t::MODE_CFG, t);
}

void store_cfg(unsigned long t) {
    debug(2, "store_cfg");

    set_state(STATE_CFG_STORE);

    cfg.store();

    cancel_cfg_timer.cancel();

    led_blink.start(led_blink_t::MODE_STORE, t);
}

void cancel_cfg(unsigned long) {
    debug(2, "cancel_cfg");

    set_state(STATE_CFG_CANCEL);

    cfg.read();

    cancel_cfg_timer.cancel();
    led_blink.cancel();

    set_state(STATE_NORMAL);
}

void check_and_print(unsigned long t) {
    if (t - last_read_time >= 1000) {
        last_read_time = t;

        sensor::read(t);

    } else {
        if (sensor::update(t)) {
            uint16_t v = sensor::value / 100;
            uint16_t m = 0x03FF >> (10 - v);

            debug(1, pwm::pulse_us, " ", pwm::low_us, " ",
                pwm::pulse_count, " ", sensor::value, " ", v, " ", m);

            if (state == STATE_NORMAL) {
                if (pwm::pulse_count < 2) {
                    led_blink.start(led_blink_t::MODE_NO_SENSOR, t);
                } else {
                    if (v < 1) {
                        led_blink.start(led_blink_t::MODE_EMPTY, t);
                    } else {
                        led_blink.set(m);
                        led_blink.cancel();
                    }
                }
            }
        }
    }
}

void loop() {
    unsigned long t = millis();

    check_and_print(t);

    if (led_blink.update(t)) {
        switch (state) {
        case STATE_INTRO:
            set_state(STATE_NORMAL);
            break;

        case STATE_CFG:
            led_blink.start(led_blink_t::MODE_CFG, t);
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

void on_hold_both(unsigned long t) {
    switch (state) {
    case STATE_NORMAL:
        start_cfg(t);
        break;

    case STATE_CFG:
        store_cfg(t);
        break;
    }
}

void empty_btn_handler::on_hold(unsigned long t) {
    debug(2, "empty::hold");

    if (full_btn.hold()) {
        on_hold_both(t);
        return;
    }

    if (full_btn.down()) { return; }

    if (state == STATE_CFG) {
        cfg.read();
        cfg.empty(last_val);

        cancel_cfg_timer.schedule(t + CANCEL_TIMEOUT);

        led_blink.start(led_blink_t::MODE_STORE, t);
        return;
    }
}

void full_btn_handler::on_hold(unsigned long t) {
    debug(2, "full::hold");

    if (empty_btn.hold()) {
        on_hold_both(t);
        return;
    }

    if (empty_btn.down()) { return; }

    if (state == STATE_CFG) {
        cfg.read();
        cfg.full(last_val);

        cancel_cfg_timer.schedule(t + CANCEL_TIMEOUT);

        led_blink.start(led_blink_t::MODE_STORE, t);
        return;
    }
}

