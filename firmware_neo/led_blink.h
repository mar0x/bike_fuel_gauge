
#pragma once

#include "artl/timer.h"
#include "artl/digital_out.h"
#include "neo/chain.h"
#include "debug.h"

struct led_blink_t : public artl::timer<> {

    enum {
        MAX_LED = 10,
    };

    enum {
        MASK_ALL = 0x03FC,
    };

    using base = artl::timer<>;

    using neo_pin = artl::digital_out<artl::pin::id::pb6>;
    using neo_chain = neo::chain_t<MAX_LED, neo_pin, neo::GRB>;
    using pixel = neo_chain::pixel_type;

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
        INTRO_FRAME_TIMEOUT = 100,
        INTRO_TIMEOUT = INTRO_FRAME_TIMEOUT * MAX_LED,

        CFG_FRAME_TIMEOUT = 200,
        CFG_ON_TIMEOUT = 200,
        CFG_OFF_TIMEOUT = 100,

        NO_SENSOR_ON_TIMEOUT = 100,
        NO_SENSOR_OFF_TIMEOUT = 1000,

        EMPTY_ON_TIMEOUT = 600,
        EMPTY_OFF_TIMEOUT = 300,
//        EMPTY_ON_TIMEOUT = 2000,
//        EMPTY_OFF_TIMEOUT = 2000,

        SET_FRAME_TIMEOUT = 60,
        SET_TIMEOUT = SET_FRAME_TIMEOUT * 14,

        RESET_TIMEOUT = 800,
        RESET_ON_TIMEOUT = 50,
        RESET_OFF_TIMEOUT = 50,
    };

    void setup();

    void start(uint8_t m, unsigned long t);
    bool update(unsigned long t);

    void cancel() { start(MODE_NORMAL, 0); }

    void set_mask(uint16_t m);
    void set_level(uint8_t l);
    void set(uint8_t i, const pixel& p);
    void off();

    static uint16_t level2mask(uint8_t l);

    uint8_t get_mode() const { return mode; }

    void set_brightness(uint8_t b);
    uint8_t get_brightness() const;
    uint8_t inc_brightness();
    uint8_t dec_brightness();

    void show();

protected:

    void set_frame(uint8_t f, unsigned long t);

    uint16_t mask = 0;
    uint16_t last_mask = 0;
    uint8_t  mode;
    uint8_t  frame;
    bool     need_show;

    const pixel *scheme;

    artl::timer<> cancel_timer;
};

led_blink_t led_blink;

void led_blink_t::setup() {
    mode = MODE_NORMAL;

    static const pixel fixed3_scheme[] = {
        {255,   0, 0},
        {255, 127, 0},
        {191, 127, 0},
        {255, 191, 0},
        {191, 191, 0},
        {191, 191, 0},
        {191, 255, 0},
        {127, 191, 0},
        {127, 225, 0},
        {  0, 255, 0},
    };
    scheme = fixed3_scheme;

    neo_chain::setup();
    neo_chain::set_brightness(0);
}

void led_blink_t::start(uint8_t m, unsigned long t) {
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
        set_mask(0x01);
        cancel_timer.cancel();
        break;

    case MODE_EMPTY:
        set_mask(0x03);
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

bool led_blink_t::update(unsigned long t) {
    if (base::update(t)) {
        set_frame(frame + 1, t);
    }

    if (cancel_timer.update(t)) {
        cancel();
        return true;
    }

    return false;
}

void led_blink_t::set_mask(uint16_t m) {
    if (m == last_mask) return;

    for (uint16_t i = 0; i < MAX_LED; i++) {
        if (m & (1 << i)) {
            neo_chain::set_pixel(MAX_LED - 1 - i, scheme[i]);
        } else {
            neo_chain::off_pixel(MAX_LED - 1 - i);
        }
    }

    last_mask = m;

    need_show = true;
}

void led_blink_t::set_level(uint8_t l) {
    mask = level2mask(l);
    if (mode == MODE_NORMAL) {
        set_mask(mask);
    } else {
        cancel();
    }
}

void led_blink_t::set(uint8_t i, const pixel& p) {
    neo_chain::set_pixel(MAX_LED - 1 - i, p);

    need_show = true;
}

void led_blink_t::off() {
    if (last_mask == 0) return;

    for (uint16_t i = 0; i < MAX_LED; i++) {
        neo_chain::off_pixel(i);
    }

    last_mask = 0;

    need_show = true;
}

uint16_t led_blink_t::level2mask(uint8_t l) {
    if (l < 1) l = 1;
    if (l > 8) l = 8;

    return (MASK_ALL >> (8 - l)) & MASK_ALL;
    //return (0x03FC >> (8 - l)) & 0x3FC;
}

void led_blink_t::set_brightness(uint8_t b) {
    if (b == get_brightness()) return;

    debug(2, "set_brightness ", b);

    neo_chain::set_brightness(b);

    need_show = true;
}

uint8_t led_blink_t::get_brightness() const {
    return neo_chain::brightness;
}

uint8_t led_blink_t::inc_brightness() {
    uint8_t b = get_brightness();

    if (b == 0) return b;

    if (b & 0x80) {
        b = 0;
    } else {
        for (uint8_t i = 0x40; i > 0; i = i >> 1) {
            if (b & i) {
                b = i << 1;
                break;
            }
        }
    }

    set_brightness(b);

    return b;
}

uint8_t led_blink_t::dec_brightness() {
    uint8_t b = get_brightness();

    if (b == 2) return b;

    if (b == 0) {
        b = 0x80;
    } else {
        for (uint8_t i = 0x80; i > 2; i = i >> 1) {
            if (b & i) {
                b = i >> 1;
                break;
            }
        }
    }

    set_brightness(b);

    return b;
}

void led_blink_t::show() {
    if (!need_show) return;

    need_show = false;

    neo_chain::show();
}

void led_blink_t::set_frame(uint8_t f, unsigned long t) {
    debug(10, "led_blink frame ", f);

    frame = f;

    switch (mode) {
    case MODE_INTRO:
        set_mask(1 << (MAX_LED - 1 - f));
        schedule(t + INTRO_FRAME_TIMEOUT);
        break;

    case MODE_NORMAL:
        set_mask(mask);
        break;

    case MODE_CFG_EMPTY:
        if (f % 2) {
            set_mask(0x01);
        } else {
            set_mask(0x02);
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
            off();
        } else {
            set_mask(level2mask(mode - MODE_CFG_START));
        }
        schedule(t + CFG_FRAME_TIMEOUT);
        break;

    case MODE_CFG_RESET:
        if (f % 2) {
            off();
        } else {
            set_mask(MASK_ALL);
        }
        schedule(t + CFG_FRAME_TIMEOUT);
        break;

    case MODE_NO_SENSOR:
        if (f % 2) {
            set_mask(0x01);
            schedule(t + NO_SENSOR_ON_TIMEOUT);
        } else {
            off();
            schedule(t + NO_SENSOR_OFF_TIMEOUT);
        }
        break;

    case MODE_EMPTY:
        if (f % 2) {
            set_mask(0x03);
            schedule(t + EMPTY_ON_TIMEOUT);
        } else {
            off();
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
            set_mask(MASK_ALL >> f);
        } else {
            if (f % 2) {
                set_mask(MASK_ALL >> frames);
            } else {
                off();
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
            set_mask(MASK_ALL >> (8 - f));
        } else {
            if (f % 2) {
                set_mask(MASK_ALL >> (8 - frames));
            } else {
                off();
            }
        }
        schedule(t + SET_FRAME_TIMEOUT);
        break;
    }

    case MODE_RESET:
        if (f % 2) {
            set_mask(MASK_ALL);
            schedule(t + RESET_ON_TIMEOUT);
        } else {
            off();
            schedule(t + RESET_OFF_TIMEOUT);
        }
        break;

    }
}
