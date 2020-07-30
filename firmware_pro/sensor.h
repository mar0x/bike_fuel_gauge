
#pragma once

#include "pwm.h"
#include "artl/timer.h"

struct sensor {

    static artl::timer<> read_timer;
    static unsigned long value;
    static bool ready;

    // period in microseconds for 120Hz
    static constexpr unsigned long max_value = 1000000 / 120;

    static void setup() {
        pwm::setup();
    }

    static void read(unsigned long t) {
        if (read_timer.active()) {
            return;
        }

        read_timer.schedule(t + 100);

        pwm::reset();
        pwm::enable();
    }

    static bool update(unsigned long t) {
        bool rc = read_timer.update(t);

        if (rc) {
            pwm::disable();

            ready = pwm::pulse_count > 1;
            value = pwm::pulse_us;
        }

        return rc;
    }
};

artl::timer<> sensor::read_timer;
unsigned long sensor::value = 0;
bool sensor::ready = false;
