
#pragma once

namespace neo {

enum order_t {
    GRB,
    GRBW,
};

template<order_t order>
struct pixel_t {
    pixel_t();
    pixel_t(uint8_t r, uint8_t g, uint8_t b, uint8_t w = 0);
    void set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t w = 0);
    void set_brightness(uint8_t br);
};


template<>
struct pixel_t<GRB> {
    uint8_t g;
    uint8_t r;
    uint8_t b;

    pixel_t() : g(0), r(0), b(0) { }

    pixel_t(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t = 0) :
        g(g_), r(r_), b(b_) { }

    void set_color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t = 0) {
        g = g_; r = r_; b = b_;
    }

    void set_brightness(uint8_t br) {
        g = (g * br) >> 8;
        r = (r * br) >> 8;
        b = (b * br) >> 8;
    }

    uint16_t glare() const { return r + g + b; }
};


template<>
struct pixel_t<GRBW> : public pixel_t<GRB> {
    using base = pixel_t<GRB>;
    uint8_t w;

    pixel_t() : w(0) { }

    pixel_t(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t w_) :
        base(r_, g_, b_), w(w_)
    {
    }

    void set_color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t w_) {
        base::set_color(r_, g_, b_, 0);
        w = w_;
    }

    void set_brightness(uint8_t br) {
        base::set_brightness(br);
        w = (w * br) >> 8;
    }

    uint16_t glare() const { return r + g + b + w; }
};

}
