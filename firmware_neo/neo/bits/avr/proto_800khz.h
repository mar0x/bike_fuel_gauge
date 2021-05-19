
#pragma once

#include "port_traits.h"

namespace neo {

template<>
struct proto_t<FREQ_800KHz> {
    static void send(uint8_t *data, uint16_t size, const port_traits_t &p) {
        noInterrupts(); // Need 100% focus on instruction timing

        volatile uint16_t i = size; // Loop counter
        volatile uint8_t *ptr = data; // Pointer to next byte
        volatile uint8_t b = *ptr++; // Current byte value
        volatile uint8_t *port = p.port_out;
        volatile uint8_t hi = *port | p.mask;
        volatile uint8_t lo = *port & ~p.mask;

        // WS2811 and WS2812 have different hi/lo duty cycles; this is
        // similar but NOT an exact copy of the prior 400-on-8 code.

        // 20 inst. clocks per bit: HHHHHxxxxxxxxLLLLLLL
        // ST instructions:         ^   ^        ^       (T=0,5,13)

        volatile uint8_t next = lo, bit = 8;

        asm volatile(
         "neo_head20:"               "\n\t" // Clk  Pseudocode    (T =  0)
          "st   %a[port],  %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
          "sbrc %[byte],  7"         "\n\t" // 1-2  if(b & 128)
           "mov  %[next], %[hi]"     "\n\t" // 0-1   next = hi    (T =  4)
          "dec  %[bit]"              "\n\t" // 1    bit--         (T =  5)
          "st   %a[port],  %[next]"  "\n\t" // 2    PORT = next   (T =  7)
          "mov  %[next] ,  %[lo]"    "\n\t" // 1    next = lo     (T =  8)
          "breq neo_nextbyte20"      "\n\t" // 1-2  if(bit == 0) (from dec above)
          "rol  %[byte]"             "\n\t" // 1    b <<= 1       (T = 10)
          "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 12)
          "nop"                      "\n\t" // 1    nop           (T = 13)
          "st   %a[port],  %[lo]"    "\n\t" // 2    PORT = lo     (T = 15)
          "nop"                      "\n\t" // 1    nop           (T = 16)
          "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 18)
          "rjmp neo_head20"          "\n\t" // 2    -> head20 (next bit out)
         "neo_nextbyte20:"           "\n\t" //                    (T = 10)
          "ldi  %[bit]  ,  8"        "\n\t" // 1    bit = 8       (T = 11)
          "ld   %[byte] ,  %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 13)
          "st   %a[port], %[lo]"     "\n\t" // 2    PORT = lo     (T = 15)
          "nop"                      "\n\t" // 1    nop           (T = 16)
          "sbiw %[count], 1"         "\n\t" // 2    i--           (T = 18)
           "brne neo_head20"         "\n"   // 2    if(i != 0) -> (next byte)
          : [port]  "+e" (port),
            [byte]  "+r" (b),
            [bit]   "+r" (bit),
            [next]  "+r" (next),
            [count] "+w" (i)
          : [ptr]    "e" (ptr),
            [hi]     "r" (hi),
            [lo]     "r" (lo));

        interrupts();
    }
};

}
