
#pragma once

namespace neo {

struct port_traits_t {
    template<typename T>
    port_traits_t(T) :
        port_out(&T::port::out()),
        mask(T::bit_mask)
    { }

    volatile uint8_t  *port_out;
    uint8_t  mask;
};

}
