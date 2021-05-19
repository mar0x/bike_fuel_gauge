
#pragma once

namespace artl {

struct default_button_handler {
    void on_down(bool, unsigned long) { }
    void on_hold(unsigned long) { }
    void on_repeat(unsigned long) { }
    void on_double_push(unsigned long) { }
};

template<unsigned long HOLD_MS>
struct hold_traits {
    bool hold() const { return hold_; }

    bool check(bool down, unsigned long state_change_time, unsigned long t) {
        if (down && !hold_ && t - state_change_time >= HOLD_MS) {
            hold_ = true;
            return true;
        }

        return false;
    }

    void reset() { hold_ = false; }

    bool hold_ = false;
};

template<>
struct hold_traits<0> {
    constexpr bool hold() const { return false; }
    constexpr bool check(bool, unsigned long, unsigned long) { return false; }
    void reset() { };
};


template<unsigned long START_MS, unsigned long REPEAT_MS>
struct repeat_traits {
    bool check(bool down, unsigned long state_change_time, unsigned long t) {
        if (down && last_repeat_time_ == 0 && t - state_change_time >= START_MS) {
            last_repeat_time_ = t;
            return true;
        }

        if (down && last_repeat_time_ != 0 && t - last_repeat_time_ >= REPEAT_MS) {
            last_repeat_time_ = t;
            return true;
        }

        return false;
    }

    void reset() { last_repeat_time_ = 0; }

    unsigned long last_repeat_time_ = 0;
};

template<unsigned long START_MS>
struct repeat_traits<START_MS, 0> {
    constexpr bool check(bool, unsigned long, unsigned long) { return false; }
    void reset() { };
};


template<unsigned long MAX_DELAY_MS>
struct double_push_traits {
    bool check(bool down, unsigned long t) {
        if (down && t - last_push_time_ <= MAX_DELAY_MS) {
            last_push_time_ = t;
            return true;
        }

        if (down) {
            last_push_time_ = t;
        }

        return false;
    }

    unsigned long last_push_time_ = 0;
};

template<>
struct double_push_traits<0> {
    constexpr bool check(bool, unsigned long) { return false; }
};


template<typename HANDLERS = default_button_handler,
         unsigned long BOUNCE_MS = 5,
         unsigned long HOLD_MS = 500,
         unsigned long REPEAT_MS = 100,
         unsigned long MAX_DOUBLE_DELAY_MS = 0>
struct button : public HANDLERS, public hold_traits<HOLD_MS>,
                public repeat_traits<HOLD_MS, REPEAT_MS>,
                public double_push_traits<MAX_DOUBLE_DELAY_MS> {

    using HANDLERS::HANDLERS;
    using hold_t = hold_traits<HOLD_MS>;
    using repeat_t = repeat_traits<HOLD_MS, REPEAT_MS>;
    using double_push_t = double_push_traits<MAX_DOUBLE_DELAY_MS>;

    enum {
        EV_NONE,
        EV_PUSH,
        EV_HOLD,
        EV_REPEAT,
        EV_RELEASE,
        EV_DOUBLE_PUSH,
    };

    bool up() const { return !down_; }
    bool down() const { return down_; }

    uint8_t update(bool down, unsigned long t) {
        if (down != down_) {
            down_ = down;
            bounce_ = true;
            state_change_time_ = t;
        }

        if (!bounce_) {
            if (hold_t::check(down_, state_change_time_, t)) {
                this->on_hold(t);

                return EV_HOLD;
            }

            if (repeat_t::check(down_, state_change_time_, t)) {
                this->on_repeat(t);

                return EV_REPEAT;
            }

            return EV_NONE;
        }

        if (t - state_change_time_ >= BOUNCE_MS) {
            bounce_ = false;
            state_change_time_ = t;
            if (down_debounced_ != down_) {
                down_debounced_ = down_;

                hold_t::reset();
                repeat_t::reset();

                if (double_push_t::check(down_, t)) {
                    this->on_double_push(t);

                    return EV_DOUBLE_PUSH;
                } else {
                    this->on_down(down_, t);

                    return down_ ? EV_PUSH : EV_RELEASE;
                }
            }
        }

        return EV_NONE;
    }

private:
    bool down_ = false;
    bool down_debounced_ = false;
    bool bounce_ = false;

    unsigned long state_change_time_ = 0;
};

}
