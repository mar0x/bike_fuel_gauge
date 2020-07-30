
#pragma once

#include "artl/timer.h"
#include "led_bar.h"
#include "debug.h"

struct led_blink_t : public artl::timer<> {
    using base = artl::timer<>;

    enum {
        MODE_INTRO,
        MODE_NORMAL,
        MODE_CFG,
        MODE_STORE,
        MODE_NO_SENSOR,
        MODE_EMPTY,
    };

    enum { // milliseconds
        INTRO_FRAME_TIMEOUT = 50,
        INTRO_TIMEOUT = INTRO_FRAME_TIMEOUT * 10,

        CFG_ON_TIMEOUT = 200,
        CFG_OFF_TIMEOUT = 100,

        STORE_TIMEOUT = 500,
        STORE_ON_TIMEOUT = 50,
        STORE_OFF_TIMEOUT = 50,

        NO_SENSOR_ON_TIMEOUT = 100,
        NO_SENSOR_OFF_TIMEOUT = 50,

        EMPTY_ON_TIMEOUT = 500,
        EMPTY_OFF_TIMEOUT = 50,
    };

    void setup() {
        mode = MODE_NORMAL;
        led_bar::setup();
    }

    void start(uint8_t m, unsigned long t) {
        if (m == mode) {
            return;
        }

        debug(3, "led_blink start ", m);

        mode = m;

        switch (mode) {
        case MODE_NORMAL:
            base::cancel();
            cancel_timer.cancel();
            break;

        case MODE_CFG:
            cancel_timer.cancel();
            break;

        case MODE_NO_SENSOR:
            led_bar::set(0x01);
            cancel_timer.cancel();
            break;

        case MODE_EMPTY:
            led_bar::set(0x03);
            cancel_timer.cancel();
            break;

        case MODE_INTRO:
            cancel_timer.schedule(t + INTRO_TIMEOUT);
            break;

        case MODE_STORE:
            cancel_timer.schedule(t + STORE_TIMEOUT);
            break;
        }

        set_frame(0, t);
    }

    bool update(unsigned long t) {
        if (base::update(t)) {
            set_frame(frame + 1, t);
        }

        if (cancel_timer.update(t)) {
            cancel();
            return true;
        }

        return false;
    }

    void cancel() {
        start(MODE_NORMAL, 0);
    }

    void set(uint16_t m) {
        mask = m;
        if (mode == MODE_NORMAL) {
            led_bar::set(m);
        }
    }

protected:
    void set_frame(uint8_t f, unsigned long t) {
        debug(10, "led_blink frame ", f);

        frame = f;

        switch (mode) {
        case MODE_INTRO:
            led_bar::set(1 << (9 - f));
            schedule(t + INTRO_FRAME_TIMEOUT);
            break;

        case MODE_NORMAL:
            led_bar::set(mask);
            break;

        case MODE_CFG:
            if (f % 2) {
                led_bar::set(mask);
                schedule(t + CFG_ON_TIMEOUT);
            } else {
                led_bar::off();
                schedule(t + CFG_OFF_TIMEOUT);
            }
            break;

        case MODE_STORE:
            if (f % 2) {
                led_bar::set(mask);
                schedule(t + STORE_ON_TIMEOUT);
            } else {
                led_bar::off();
                schedule(t + STORE_OFF_TIMEOUT);
            }
            break;

        case MODE_NO_SENSOR:
            if (f % 2) {
                led_bar::set(mask);
                schedule(t + NO_SENSOR_ON_TIMEOUT);
            } else {
                led_bar::off();
                schedule(t + NO_SENSOR_OFF_TIMEOUT);
            }
            break;

        case MODE_EMPTY:
            if (f % 2) {
                led_bar::set(mask);
                schedule(t + EMPTY_ON_TIMEOUT);
            } else {
                led_bar::off();
                schedule(t + EMPTY_OFF_TIMEOUT);
            }
            break;

        }
    }

    uint16_t mask = 0;
    uint8_t  mode;
    uint8_t  frame;

    artl::timer<> cancel_timer;
};

led_blink_t led_blink;

