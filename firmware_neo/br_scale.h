#pragma once

struct br_scale {
    enum {
        MAX_BR_SCALE = 22,
    };

    void setup() {
        unsigned long b = 4;

        for (uint8_t i = 0; i < MAX_BR_SCALE; ++i) {
            scale[i] = b;
            b = b * 5 / 4;
        }

        scale[MAX_BR_SCALE - 1] = 0xFF;
    }

    uint8_t scale[MAX_BR_SCALE];

    uint8_t id(uint8_t br) {
        uint8_t l = 0, r = MAX_BR_SCALE, i;

        while (l + 1 < r) {
            i = (l + r) / 2;
            if (scale[i] == br) return i;

            if (scale[i] > br) {
                r = i;
            } else {
                l = i;
            }
        }

        return l;
    }

    uint8_t next(uint8_t br) {
        uint8_t i = id(br);

        debug(6, "br::next: ", i);

        if (i < MAX_BR_SCALE - 1) ++i;

        return scale[i];
    }

    uint8_t prev(uint8_t br) {
        uint8_t i = id(br);

        debug(6, "br::prev: ", i);

        if (i > 0) --i;

        return scale[i];
    }
};
