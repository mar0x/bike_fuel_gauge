
/*
~/Library/Arduino15/packages/arduino/hardware/avr/1.8.2/variants/leonardo/pins_arduino.h
need to be patched: TXLED D5 should be changed for D4
*/

#include "debug.h"
#include "sensor.h"
#include "config.h"
#include "led_blink.h"
#include "filter.h"
#include "serial_cmd.h"
#include "br_scale.h"
#include "artl/button.h"
#include "artl/digital_out.h"
#include "artl/digital_in.h"
#include "artl/timer.h"
#include "artl/yield.h"


enum { // milliseconds
    CANCEL_TIMEOUT = 15000, // 15 sec
    FUEL_SENSOR_PERIOD = 500,
    LIGHT_SENSOR_PERIOD = 500,
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

using b_empty = artl::digital_in<artl::pin::id::pd3>;
using b_full = artl::digital_in<artl::pin::id::pd5>;

artl::timer<> cancel_cfg_timer;
artl::timer<> fuel_sensor_timer;
artl::timer<> light_sensor_timer;

uint8_t state = STATE_INTRO;

bool sensor_simulation = false;

config_t cfg;
serial_cmd_t scmd;
br_scale br;

#define HW_VERSION "2020.09.22"
#define FW_VERSION "2020.10.02"

const char version[] PROGMEM =
    "HW " HW_VERSION "\n"
    "FW " FW_VERSION "\n"
    "BD " __DATE__ "\n"
    "BT " __TIME__ "\n";

struct empty_btn_handler : public artl::default_button_handler {
    void on_down(bool, unsigned long);
    void on_hold(unsigned long);
    void on_repeat(unsigned long);
    void on_double_push(unsigned long);
};

struct full_btn_handler : public artl::default_button_handler {
    void on_down(bool, unsigned long);
    void on_hold(unsigned long);
    void on_repeat(unsigned long);
    void on_double_push(unsigned long);
};

artl::button<empty_btn_handler, 5, 1000, 100, 500> empty_btn;
artl::button<full_btn_handler, 5, 1000, 100, 500> full_btn;
filter_t fuel_sensor_filter;
filter_t light_sensor_filter;

void set_state(uint8_t s, unsigned long t) {
    state = s;

    switch (state) {
    case STATE_INTRO:
        debug(2, "state ", state, " intro");
        led_blink.start(led_blink_t::MODE_INTRO, t);
        break;

    case STATE_NORMAL:
        debug(2, "state ", state, " normal");
        break;

    case STATE_CFG:
        debug(2, "state ", state, " cfg");
        cancel_cfg_timer.schedule(t + CANCEL_TIMEOUT);
        led_blink.start(led_blink_t::MODE_CFG_START, t);
        break;

    case STATE_CFG_CANCEL:
        debug(2, "state ", state, " cfg cancel");
        cfg.read();

        cancel_cfg_timer.cancel();
        led_blink.cancel();

        state = STATE_NORMAL;
        break;

    case STATE_CFG_SET_FULL:
    case STATE_CFG_SET_LOW:
        break;

    case STATE_CFG_STORE: {
        debug(2, "state ", state, " cfg store");
        cancel_cfg_timer.cancel();

        uint8_t m = led_blink.get_mode() - led_blink_t::MODE_CFG_START;

        if (m < config_t::MAX_LED) {
            cfg.set(m, fuel_sensor_filter);
            led_blink.start(led_blink_t::MODE_SET_START + m, t);
        } else {
            cfg.reset();
            led_blink.start(led_blink_t::MODE_RESET, t);
        }

        break;
    }
    }
}

void setup() {
    unsigned long t = millis();

    Serial.begin(115200);
    debug_level_ = 5;

    br.setup();

    sensor::setup();
    led_blink.setup();

    cfg.read();

    fuel_sensor_timer.schedule(t);
    light_sensor_timer.schedule(t);

    set_state(STATE_INTRO, t);

    artl::yield();
}

void update_led(unsigned long sensor_val, unsigned long t) {
    if (!sensor_simulation && !sensor::ready) {
        led_blink.start(led_blink_t::MODE_NO_SENSOR, t);
        return;
    }

    uint16_t v = cfg.led(sensor_val);
    if (v < 1) {
        led_blink.start(led_blink_t::MODE_EMPTY, t);
        return;
    }

    led_blink.set_level(v);
}

void check_sensor(unsigned long t) {
    if (sensor_simulation) { return; }

    if (fuel_sensor_timer.update(t)) {
        sensor::read(t);

        return;
    }

    if (sensor::update(t)) {
        fuel_sensor_timer.schedule(t + FUEL_SENSOR_PERIOD);

        unsigned long sv = sensor::value;

        if (empty_btn.down() || state == STATE_INTRO) {
            sv = fuel_sensor_filter.update(sv, 0);
        } else {
            sv = fuel_sensor_filter.update(sv, t);
        }

        debug(6, pwm::pulse_us, " ", pwm::low_us, " ",
            pwm::pulse_count, " ", sensor::value, " ", sv, " ",
            fuel_sensor_filter.mean_, " ", fuel_sensor_filter.cov_);

        if (state == STATE_NORMAL) {
            update_led(sv, t);
        }
    }
}

void check_light(unsigned long t) {
    if (light_sensor_timer.update(t)) {
        light_sensor_timer.schedule(t + LIGHT_SENSOR_PERIOD);

        unsigned long v = analogRead(artl::pin::id::pb5);
        light_sensor_filter.update(v, t);

        debug(6, "light ",  v, " ",
            (unsigned long) light_sensor_filter, " ",
            light_sensor_filter.mean_, " ", light_sensor_filter.cov_);
    }
}

void print_pgm(const char *s, uint16_t size) {
    for (uint16_t i = 0; i < size; ++i) {
        char b = pgm_read_byte_near(s + i);
        if (b == '\n') { Serial.print('\r'); }
        Serial.print(b);
    }
}

template<typename T> void sprintln(const T& a) {
    Serial.println(a);
}

template<typename T, typename ...Args> void sprintln(const T& a, Args... args) {
    Serial.print(a);
    sprintln(args...);
}

void process_serial_cmd(unsigned long t) {
    char cmd[4];
    scmd.get_arg(0, cmd);
    cmd[3] = 0;

    sprintln("");

    switch (scmd.command()) {
    case serial_cmd_t::CMD_VERSION:
        print_pgm(version, sizeof(version));
        break;

    case serial_cmd_t::CMD_HELP:
        print_pgm(help, sizeof(help));
        break;

    case serial_cmd_t::CMD_STATE: {
        uint8_t p;
        if (scmd.get_arg(1, p)) { set_state(p, t); }

        sprintln(cmd, state);
        break;
    }
    case serial_cmd_t::CMD_FUEL_SENSOR: {
        unsigned long sv = 0;
        if (scmd.get_arg(1, sv)) {
            sensor_simulation = true;

            sv = fuel_sensor_filter.update(sv, 0);

            if (state == STATE_NORMAL) {
                update_led(sv, t);
            }
        } else {
            sensor_simulation = false;

            fuel_sensor_timer.schedule(t);

            sv = sensor::value;
        }

        sprintln(cmd, sv);
        break;
    }
    case serial_cmd_t::CMD_BRIGHTNESS: {
        uint8_t b;
        if (scmd.get_arg(1, b)) { led_blink.set_brightness(b); }

        sprintln(cmd, led_blink.get_brightness());
        break;
    }
    case serial_cmd_t::CMD_LIGHT_SENSOR:
        sprintln(cmd, analogRead(artl::pin::id::pb5));
        break;

    case serial_cmd_t::CMD_GRID: {
        uint8_t b;
        if (scmd.get_arg(1, b)) {
            uint16_t v;
            if (scmd.get_arg(2, v)) {
                cfg.set(b, v);
            }

            sprintln(cmd, b, " ", cfg.get(b));
        } else {
            Serial.print("GR");
            for (uint8_t i = 0; i < config_t::MAX_LED; ++i) {
                Serial.print(" ");
                Serial.print(cfg.get(i));
            }
            Serial.println("");
        }
        break;
    }
    case serial_cmd_t::CMD_COLOR_SCHEME: {
        break;
    }
    case serial_cmd_t::CMD_LED_COLOR: {
        uint8_t n, r, g, b;
        if (scmd.get_arg(1, n, r, g, b) && n < led_blink_t::MAX_LED) {
            led_blink.set(n, led_blink_t::pixel(r, g, b));
        }
        break;
    }
    case serial_cmd_t::CMD_DEBUG_LEVEL:
        uint8_t l;
        if (scmd.get_arg(1, l)) {
            debug_level_ = l;
        }
        sprintln(cmd, debug_level_);
        break;

    case serial_cmd_t::CMD_FACTORY_RESET: {
        break;
    }
    }

    scmd.reset();

    Serial.print("> ");
}

void loop() {
    unsigned long t = millis();

    check_sensor(t);
    check_light(t);

    if (led_blink.update(t)) {
        switch (state) {
        case STATE_INTRO:
            set_state(STATE_NORMAL, t);
            break;

        case STATE_CFG:
            led_blink.start(led_blink_t::MODE_CFG_START, t);
            break;

        case STATE_CFG_STORE:
            set_state(STATE_NORMAL, t);
            break;
        }
    }

    if (cancel_cfg_timer.update(t)) {
        set_state(STATE_CFG_CANCEL, t);
    }

    empty_btn.update(b_empty::read() == 0, t);
    full_btn.update(b_full::read() == 0, t);

    while (!scmd && Serial.available()) {
        uint8_t b = Serial.read();

        scmd.read(b);

        // Serial echo
        // out_.serial_print((char) b);
    }

    if (scmd) {
        process_serial_cmd(t);
    }

    if (!sensor::active()) {
        led_blink.show();
    }

    artl::yield();
}

void empty_btn_handler::on_down(bool down, unsigned long t) {
    debug(4, "empty::down ", down, " ", sizeof(empty_btn));

    if (!down) { return; }

    if (state == STATE_CFG) {
        uint8_t m = led_blink.get_mode() - led_blink_t::MODE_CFG_START;
        const uint8_t cfg_count = led_blink_t::MODE_CFG_END - led_blink_t::MODE_CFG_START;
        m = (m + 1) % cfg_count;

        led_blink.start(led_blink_t::MODE_CFG_START + m, t);

        cancel_cfg_timer.schedule(t + CANCEL_TIMEOUT);
    }

    if (state == STATE_NORMAL && !full_btn.down()) {
        led_blink.dec_brightness();
    }
}

void empty_btn_handler::on_hold(unsigned long t) {
    debug(4, "empty::hold");

    if (full_btn.hold() && state == STATE_NORMAL) {
        set_state(STATE_CFG, t);
    }
}

void empty_btn_handler::on_repeat(unsigned long) {
    debug(4, "empty::repeat");

    if (state == STATE_NORMAL && !full_btn.down()) {
        led_blink.dec_brightness();
    }
}

void empty_btn_handler::on_double_push(unsigned long) {
    debug(4, "empty::double_push");
}

void full_btn_handler::on_down(bool down, unsigned long t) {
    debug(4, "full::down ", down, " ", sizeof(full_btn));

    if (!down) { return; }

    if (state == STATE_CFG) {
        cancel_cfg_timer.schedule(t + CANCEL_TIMEOUT);
    }

    if (state == STATE_NORMAL && !empty_btn.down()) {
        led_blink.inc_brightness();
    }
}

void full_btn_handler::on_hold(unsigned long t) {
    debug(4, "full::hold");

    if (empty_btn.hold() && state == STATE_NORMAL) {
        set_state(STATE_CFG, t);
        return;
    }

    if (state == STATE_CFG && !empty_btn.down()) {
        set_state(STATE_CFG_STORE, t);
    }
}

void full_btn_handler::on_repeat(unsigned long) {
    debug(4, "full::repeat");

    if (state == STATE_NORMAL && !empty_btn.down()) {
        led_blink.inc_brightness();
    }
}

void full_btn_handler::on_double_push(unsigned long) {
    debug(4, "full::double_push");
}

