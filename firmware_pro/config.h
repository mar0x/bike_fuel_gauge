
#pragma once

#include <EEPROM.h>
#include "sensor.h"
#include "debug.h"

struct config_t {

    enum {
        MAX_LED = 9,
        MAX_VALUE = sensor::max_value,
    };

    enum {
        DEF_VALUE = 0xFFFFu,
    };

    void read() {
        EEPROM.get(0, grid_);

        debug(3, "config::read: raw ",
            grid_[0], " ", grid_[1], " ", grid_[2], " ",
            grid_[3], " ", grid_[4], " ", grid_[5], " ",
            grid_[6], " ", grid_[7], " ", grid_[8]);

        if (grid_[0] > MAX_VALUE) {
            grid_[0] = 0;
        }

        if (grid_[MAX_LED - 1] > MAX_VALUE) {
            grid_[MAX_LED - 1] = MAX_VALUE;
        }

        uint8_t last_defined = 0;
        uint16_t last_value = grid_[0];

        for (uint8_t i = 1; i < MAX_LED; ++i) {
            if (grid_[i] > MAX_VALUE) {
                continue;
            }

            if (grid_[i] < last_value) {
                continue;
            }

            if (last_defined + 1 == i) {
                last_defined = i;
                last_value = grid_[i];
                continue;
            }

            uint16_t step = (grid_[i] - last_value) / (i - last_defined);

            for (uint8_t j = last_defined + 1; j < i; ++j) {
                grid_[j] = last_value + (j - last_defined) * step;
            }

            last_defined = i;
            last_value = grid_[i];
        }

        debug(3, "config::read: complete ",
            grid_[0], " ", grid_[1], " ", grid_[2], " ",
            grid_[3], " ", grid_[4], " ", grid_[5], " ",
            grid_[6], " ", grid_[7], " ", grid_[8]);
    }

    void reset() {
        debug(3, "config::reset");

        uint16_t def = DEF_VALUE;
        for (uint8_t i = 0; i < MAX_LED; ++i) {
            EEPROM.put(i * 2, def);
        }

        read();
    }

    void set(uint8_t n, uint16_t v) {
        debug(3, "config::set [", n, "] ", v);

        const uint16_t min_value = n * 2;
        if (v < min_value) {
            v = min_value;
        }

        const uint16_t max_value = MAX_VALUE - (MAX_LED - 1 - n) * 2;
        if (v > max_value) {
            v = max_value;
        }

        uint16_t grid_max = v;
        for (uint8_t i = n; i > 0; --i) {
            if (grid_[i - 1] >= grid_max) {
                grid_[i - 1] = grid_max - 2;
                grid_max -= 2;
            }
        }

        uint16_t grid_min = v;
        for (uint8_t i = n + 1; i < MAX_LED; ++i) {
            if (grid_[i] <= grid_min) {
                grid_[i] = grid_min + 2;
                grid_min += 2;
            }
        }

        grid_[n] = v;

        for (uint8_t i = 0; i < MAX_LED; ++i) {
            uint16_t g;
            EEPROM.get(i * 2, g);

            if (i == n || (g != grid_[i] && g != DEF_VALUE)) {
                debug(3, "config::set: put [", i, "] ", grid_[i]);

                EEPROM.put(i * 2, grid_[i]);
            }
        }

        read();
    }

    uint16_t led(uint16_t v) const {
        for (uint8_t i = 0; i < MAX_LED - 1; ++i) {
            if (v < (grid_[i] + grid_[i + 1]) / 2) {
                return i;
            }
        }

        return MAX_LED - 1;
    }

private:
    uint16_t grid_[MAX_LED];
};
