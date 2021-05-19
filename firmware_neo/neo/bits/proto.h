
#pragma once

#include "freq.h"

#ifdef __AVR__
#include "avr/port_traits.h"
#endif

namespace neo {

template<freq_t freq>
struct proto_t {
    static void send(uint8_t *data, uint16_t size, const port_traits_t &p);
};

}

#ifdef __AVR__
#include "avr/proto_800khz.h"
#endif

