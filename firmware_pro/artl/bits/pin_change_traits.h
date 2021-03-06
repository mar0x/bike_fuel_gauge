
#pragma once

#include <stdint.h>
#include <avr/io.h>

namespace artl {

template<uint8_t N>
struct pin_change_mask {
};

#ifdef PCMSK

template<>
struct pin_change_mask<0> {
    static volatile uint8_t& msk() { return PCMSK; }

    constexpr static uint8_t icr_bit_mask = 1 << PCIE;
};

#else

#ifdef PCMSK0

template<>
struct pin_change_mask<0> {
    static volatile uint8_t& msk() { return PCMSK0; }

    constexpr static uint8_t icr_bit_mask = 1 << PCIE0;
};

#endif

#endif

#ifdef PCMSK1

template<>
struct pin_change_mask<1> {
    static volatile uint8_t& msk() { return PCMSK1; }

    constexpr static uint8_t icr_bit_mask = 1 << PCIE1;
};

#endif

#ifdef PCMSK2

template<>
struct pin_change_mask<2> {
    static volatile uint8_t& msk() { return PCMSK2; }

    constexpr static uint8_t icr_bit_mask = 1 << PCIE2;
};

#endif

template<uint8_t PIN_NO>
struct pin_change_traits {
};

template<uint8_t MSK, uint8_t BIT_NO>
struct base_pin_change_traits {

    using mask = pin_change_mask<MSK>;

    constexpr static uint8_t icr_bit_mask = mask::icr_bit_mask;

    constexpr static uint8_t bit_mask = 1 << BIT_NO;

    static void enable() { mask::msk() |= bit_mask; }

    static void disable() { mask::msk() &= ~bit_mask; }
};

}

#ifdef ARDUINO_AVR_MINI
#define ARTL_PINOUT_STANDARD
#endif

#ifdef ARDUINO_AVR_PRO
#define ARTL_PINOUT_STANDARD
#endif

#ifdef ARDUINO_AVR_UNO
#define ARTL_PINOUT_STANDARD
#endif

#ifdef ARDUINO_AVR_LEONARDO
#include "variants/leonardo/pin_change_traits.h"
#endif

#ifdef ARTL_PINOUT_STANDARD
#include "variants/standard/pin_change_traits.h"
#endif

#ifdef ARDUINO_attiny
#include "variants/tiny14/pin_change_traits.h"
#endif
