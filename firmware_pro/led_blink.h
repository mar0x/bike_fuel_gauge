
#pragma once

#include "artl/timer.h"
#include "led_bar.h"
#include "debug.h"

struct led_blink_t : public artl::timer<> {
    using base = artl::timer<>;

    enum {
        MODE_INTRO,
        MODE_NORMAL,
        MODE_CFG_START,
        MODE_CFG_EMPTY = MODE_CFG_START,
        MODE_CFG_1,
        MODE_CFG_2,
        MODE_CFG_3,
        MODE_CFG_4,
        MODE_CFG_5,
        MODE_CFG_6,
        MODE_CFG_7,
        MODE_CFG_FULL,
        MODE_CFG_RESET,
        MODE_CFG_END,
        MODE_NO_SENSOR = MODE_CFG_END,
        MODE_EMPTY,
        MODE_SET_START,
        MODE_SET_EMPTY = MODE_SET_START,
        MODE_SET_1,
        MODE_SET_2,
        MODE_SET_3,
        MODE_SET_4,
        MODE_SET_5,
        MODE_SET_6,
        MODE_SET_7,
        MODE_SET_FULL,
        MODE_SET_END,
        MODE_RESET = MODE_SET_END,
    };

    enum { // milliseconds
        INTRO_FRAME_TIMEOUT = 50,
        INTRO_TIMEOUT = INTRO_FRAME_TIMEOUT * 10,

        CFG_FRAME_TIMEOUT = 200,
        CFG_ON_TIMEOUT = 200,
        CFG_OFF_TIMEOUT = 100,

        NO_SENSOR_ON_TIMEOUT = 100,
        NO_SENSOR_OFF_TIMEOUT = 1000,

        EMPTY_ON_TIMEOUT = 600,
        EMPTY_OFF_TIMEOUT = 300,

        SET_FRAME_TIMEOUT = 60,
        SET_TIMEOUT = SET_FRAME_TIMEOUT * 14,

        RESET_TIMEOUT = 800,
        RESET_ON_TIMEOUT = 50,
        RESET_OFF_TIMEOUT = 50,
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

        case MODE_CFG_EMPTY:
        case MODE_CFG_1:
        case MODE_CFG_2:
        case MODE_CFG_3:
        case MODE_CFG_4:
        case MODE_CFG_5:
        case MODE_CFG_6:
        case MODE_CFG_7:
        case MODE_CFG_FULL:
        case MODE_CFG_RESET:
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

        case MODE_SET_EMPTY:
        case MODE_SET_1:
        case MODE_SET_2:
        case MODE_SET_3:
        case MODE_SET_4:
        case MODE_SET_5:
        case MODE_SET_6:
        case MODE_SET_7:
        case MODE_SET_FULL:
            cancel_timer.schedule(t + SET_TIMEOUT);
            break;

        case MODE_RESET:
            cancel_timer.schedule(t + RESET_TIMEOUT);
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
        } else {
            cancel();
        }
    }

    static uint16_t level2mask(uint8_t l) {
        if (l < 1) l = 1;
        if (l > 8) l = 8;

        return (0x03FC >> (8 - l)) & 0x3FC;
    }

    uint8_t get_mode() const {
        return mode;
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

        case MODE_CFG_EMPTY:
            if (f % 2) {
                led_bar::set(0x01);
            } else {
                led_bar::set(0x02);
            }
            schedule(t + CFG_FRAME_TIMEOUT);
            break;

        case MODE_CFG_1:
        case MODE_CFG_2:
        case MODE_CFG_3:
        case MODE_CFG_4:
        case MODE_CFG_5:
        case MODE_CFG_6:
        case MODE_CFG_7:
        case MODE_CFG_FULL:
            if (f % 2) {
                led_bar::off();
            } else {
                led_bar::set(level2mask(mode - MODE_CFG_START));
            }
            schedule(t + CFG_FRAME_TIMEOUT);
            break;

        case MODE_CFG_RESET:
            if (f % 2) {
                led_bar::off();
            } else {
                led_bar::set(0x03FF);
            }
            schedule(t + CFG_FRAME_TIMEOUT);
            break;

        case MODE_NO_SENSOR:
            if (f % 2) {
                led_bar::set(0x01);
                schedule(t + NO_SENSOR_ON_TIMEOUT);
            } else {
                led_bar::off();
                schedule(t + NO_SENSOR_OFF_TIMEOUT);
            }
            break;

        case MODE_EMPTY:
            if (f % 2) {
                led_bar::set(0x03);
                schedule(t + EMPTY_ON_TIMEOUT);
            } else {
                led_bar::off();
                schedule(t + EMPTY_OFF_TIMEOUT);
            }
            break;

        case MODE_SET_EMPTY:
        case MODE_SET_1:
        case MODE_SET_2:
        case MODE_SET_3:
        case MODE_SET_4: {
            const uint8_t frames = 8 - (mode - MODE_SET_START);
            if (f < frames) {
                led_bar::set(0x3FF >> f);
            } else {
                if (f % 2) {
                    led_bar::set(0x3FF >> frames);
                } else {
                    led_bar::off();
                }
            }
            schedule(t + SET_FRAME_TIMEOUT);
            break;
        }

        case MODE_SET_5:
        case MODE_SET_6:
        case MODE_SET_7:
        case MODE_SET_FULL: {
            const uint8_t frames = mode - MODE_SET_START;
            if (f < frames) {
                led_bar::set(0x3FF >> (8 - f));
            } else {
                if (f % 2) {
                    led_bar::set(0x3FF >> (8 - frames));
                } else {
                    led_bar::off();
                }
            }
            schedule(t + SET_FRAME_TIMEOUT);
            break;
        }

        case MODE_RESET:
            if (f % 2) {
                led_bar::set(0x3FF);
                schedule(t + RESET_ON_TIMEOUT);
            } else {
                led_bar::off();
                schedule(t + RESET_OFF_TIMEOUT);
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
