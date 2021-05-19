
#pragma once

#include "artl/digital_out.h"
#include "neo/chain.h"

class led_bar {
    using neo_pin = artl::digital_out<artl::pin::id::pb6>;
    using neo_chain = neo::chain_t<10, neo_pin, neo::GRB>;

    static bool need_update;

public:
    using pixel = neo_chain::pixel_type;

    static const pixel red, green, blue, yellow, white;
    static const pixel *scheme;
    static const pixel fixed0_scheme[];
    static const pixel fixed1_scheme[];
    static const pixel fixed2_scheme[];
    static const pixel fixed3_scheme[];

    static void setup() {
        neo_chain::setup();
        neo_chain::set_brightness(0);
    }

    static void set_brightness(uint8_t b) {
        debug(2, "set_brightness ", b);

        neo_chain::set_brightness(b);

        need_update = true;
    }

    static uint8_t get_brightness() {
        return neo_chain::brightness;
    }

    static void set(uint16_t m) {

        for (uint16_t i = 0; i < 10; i++) {
            if (m & (1 << i)) {
                neo_chain::set_pixel(9 - i, scheme[i]);
            } else {
                neo_chain::set_pixel(9 - i, 0, 0, 0);
            }
        }

        need_update = true;
    }

    static void set(uint8_t i, const pixel& p) {
        neo_chain::set_pixel(9 - i, p);

        need_update = true;
    }

    static void off() {
        for (uint16_t i = 0; i < 10; i++) {
            neo_chain::set_pixel(i, 0, 0, 0);
        }

        need_update = true;
    }

    static void update() {
        if (!need_update) { return; }

        need_update = false;
        neo_chain::show();
        glare = neo_chain::bpixels[9].glare();
    }

    static uint16_t glare;
};

bool led_bar::need_update = true;
uint16_t led_bar::glare = 0;

const led_bar::pixel led_bar::red(255, 0, 0);
const led_bar::pixel led_bar::green(0, 255, 0);
const led_bar::pixel led_bar::blue(0, 0, 255);
const led_bar::pixel led_bar::yellow(150, 127, 0);
const led_bar::pixel led_bar::white(255, 255, 255);

const led_bar::pixel *led_bar::scheme = led_bar::fixed3_scheme;

const led_bar::pixel led_bar::fixed0_scheme[] = {
    red,
    red,
    yellow,
    yellow,
    yellow,
    yellow,
    green,
    green,
    green,
    green,
};

const led_bar::pixel led_bar::fixed1_scheme[] = {
    red,
    red,
    {192, 64, 0},
    yellow,
    yellow,
    yellow,
    {127, 150, 0},
    green,
    green,
    green,
};

const led_bar::pixel led_bar::fixed2_scheme[] = {
    red,
    {227,  28, 0},
    {198,  57, 0},
    {170,  85, 0},
    {142, 113, 0},
    {113, 142, 0},
    { 85, 170, 0},
    { 57, 198, 0},
    { 28, 227, 0},
    green,
};

const led_bar::pixel led_bar::fixed3_scheme[] = {
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
