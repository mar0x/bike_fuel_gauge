
#pragma once

#include "artl/digital_in.h"
#include "artl/pin_change_int.h"


struct pwm {
    enum {
        pin = artl::pin::id::pb7,
    };

    using in = artl::digital_in<pin>;
    using intr = artl::pin_change_int<pin>;

    static uint8_t state;
    static unsigned long changed_at_us;
    static unsigned long pulse_us;
    static unsigned long low_us;
    static unsigned long pulse_count;

    static void setup() {
        in::setup();
    }

    static void reset() {
        pulse_count = 0;
        pulse_us = 0;
        low_us = 0;
    }

    static void enable() {
        state = in::read();

        intr::enable();
    }

    static void disable() {
        intr::disable();
    }

    static void on_change() {
        uint8_t s = in::read();

        if (s == state) {
            return;
        }

        unsigned long now = micros();

        if (s) {
            low_us = now - changed_at_us;
        } else {
            pulse_us = now - changed_at_us;
            ++pulse_count;
        }

        changed_at_us = now;
        state = s;
    }
};

uint8_t pwm::state = 0;
unsigned long pwm::changed_at_us = 0;
unsigned long pwm::pulse_us = 0;
unsigned long pwm::low_us = 0;
unsigned long pwm::pulse_count = 0;

ISR(PCINT0_vect) {
    pwm::on_change();
}

