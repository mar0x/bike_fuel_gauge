
#pragma once

#include "pixel.h"
#include "bits/proto.h"

namespace neo {

template<uint16_t n, typename pin_t, order_t order, freq_t freq = FREQ_800KHz>
struct chain_t {
    using pixel_type = pixel_t<order>;
    using proto_type = proto_t<freq>;
    using pin_traits = typename pin_t::traits;

    static void setup() {
        pin_t::output();

        brightness = 0;
        end_time = 0;

        memset(pixels, 0, sizeof(pixels));
        memset(bpixels, 0, sizeof(bpixels));
    }

    static constexpr uint8_t size() {
        return n;
    }

    static void set_pixel(uint16_t i, uint8_t r, uint8_t g, uint8_t b, uint8_t w = 0) {
        pixels[i].set_color(r, g, b, w);
        bpixels[i].set_color(r, g, b, w);
        if (brightness) {
            bpixels[i].set_brightness(brightness);
        }
    }

    static void off_pixel(uint16_t i) {
        pixels[i].set_color(0, 0, 0, 0);
        bpixels[i].set_color(0, 0, 0, 0);
    }

    static void set_pixel(uint16_t i, const pixel_type& p) {
        pixels[i] = p;
        bpixels[i] = p;
        if (brightness) {
            bpixels[i].set_brightness(brightness);
        }
    }

    static void set_brightness(uint8_t br) {
        if (br == brightness) return;
        brightness = br;

        memcpy(bpixels, pixels, sizeof(pixels));

        if (brightness) {
            for (uint8_t i = 0; i < n; ++i) {
                bpixels[i].set_brightness(brightness);
            }
        }
    }

    static void show() {
        // Data latch = 50+ microsecond pause in the output stream.  Rather than
        // put a delay at the end of the function, the ending time is noted and
        // the function will simply hold off (if needed) on issuing the
        // subsequent round of data until the latch time has elapsed.  This
        // allows the mainline code to start generating the next frame of data
        // rather than stalling for the latch.
        while(!can_show());
        // endTime is a private member (rather than global var) so that mutliple
        // instances on different pins can be quickly issued in succession (each
        // instance doesn't delay the next).

        // In order to make this code runtime-configurable to work with any pin,
        // SBI/CBI instructions are eschewed in favor of full PORT writes via the
        // OUT or ST instructions.  It relies on two facts: that peripheral
        // functions (such as PWM) take precedence on output pins, so our PORT-
        // wide writes won't interfere, and that interrupts are globally disabled
        // while data is being issued to the LEDs, so no other code will be
        // accessing the PORT.  The code takes an initial 'snapshot' of the PORT
        // state, computes 'pin high' and 'pin low' values, and writes these back
        // to the PORT register as needed.

        pin_traits t;

        proto_type::send((uint8_t *) bpixels, sizeof(bpixels), port_traits_t(t));

        end_time = micros(); // Save EOD time for latch on next call
    }

    static bool can_show(void) { return (micros() - end_time) >= 50L; }

    static pixel_type pixels[n];
    static pixel_type bpixels[n];
    static uint8_t brightness;
    static unsigned long end_time;
};

template<uint16_t n, typename pin_t, order_t order, freq_t freq>
typename chain_t<n, pin_t, order, freq>::pixel_type chain_t<n, pin_t, order, freq>::pixels[n];

template<uint16_t n, typename pin_t, order_t order, freq_t freq>
typename chain_t<n, pin_t, order, freq>::pixel_type chain_t<n, pin_t, order, freq>::bpixels[n];

template<uint16_t n, typename pin_t, order_t order, freq_t freq>
uint8_t chain_t<n, pin_t, order, freq>::brightness;

template<uint16_t n, typename pin_t, order_t order, freq_t freq>
unsigned long chain_t<n, pin_t, order, freq>::end_time;

}
