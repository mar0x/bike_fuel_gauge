
#pragma once

#include <EEPROM.h>
#include "sensor.h"

struct config_t {

    void read() {
        EEPROM.get(0, *this);

        if (full_ == 0) full_ = sensor::max_value;
        if (full_ <= empty_) full_ = empty_ + 1;
    }

    void store() const {
        EEPROM.put(0, *this);
    }

    void empty(uint16_t v) {
        empty_ = v;
        if (full_ <= empty_) full_ = empty_ + 1;
    }

    void full(uint16_t v) {
        full_ = v;
        if (full_ <= empty_) full_ = empty_ + 1;
    }

    uint16_t led(uint16_t v) const {
        if (v <= empty_) { return 0; }
        if (v >= full_) { return 8; }

        return 1 + (v - empty_) * 8 / (full_ - empty_);
    }

private:
    uint16_t empty_ = 0;
    uint16_t full_ = sensor::max_value;
};

