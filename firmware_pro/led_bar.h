
#pragma once

#include "artl/digital_out.h"

class led_bar {
    using led0 = artl::digital_out<A0>;
    using led1 = artl::digital_out<15>;
    using led2 = artl::digital_out<14>;
    using led3 = artl::digital_out<16>;
    using led4 = artl::digital_out<10>;
    using led5 = artl::digital_out<5>;
    using led6 = artl::digital_out<6>;
    using led7 = artl::digital_out<7>;
    using led8 = artl::digital_out<8>;
    using led9 = artl::digital_out<9>;

public:
    static void setup() {
        led0::setup();
        led1::setup();
        led2::setup();
        led3::setup();
        led4::setup();
        led5::setup();
        led6::setup();
        led7::setup();
        led8::setup();
        led9::setup();
    }

    static void set(uint16_t m) {
        led0::write(m & (1 << 0));
        led1::write(m & (1 << 1));
        led2::write(m & (1 << 2));
        led3::write(m & (1 << 3));
        led4::write(m & (1 << 4));
        led5::write(m & (1 << 5));
        led6::write(m & (1 << 6));
        led7::write(m & (1 << 7));
        led8::write(m & (1 << 8));
        led9::write(m & (1 << 9));
    }

    static void off() {
        led0::low();
        led1::low();
        led2::low();
        led3::low();
        led4::low();
        led5::low();
        led6::low();
        led7::low();
        led8::low();
        led9::low();
    }
};
