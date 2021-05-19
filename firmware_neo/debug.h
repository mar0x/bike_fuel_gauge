
#pragma once

#define DEBUG 1

#if defined(DEBUG) && defined(HAVE_HWSERIAL1)

static uint8_t debug_level_ = 6;

template<typename T1> void debug__(const T1& a1) {
    Serial.println(a1);
}

template<typename T1, typename ...Args> void debug__(const T1& a1, Args... args) {
    Serial.print(a1);
    debug__(args...);
}

template<typename T1, typename ...Args> void debug(uint8_t l, const T1& a1, Args... args) {
    if (l <= debug_level_) {
        debug__(a1, args...);
    }
}

#else

#define debug(...)

#endif

