
#pragma once

namespace artl {

struct default_button_handler {
    void on_down(bool, unsigned long) { }
    void on_hold(unsigned long) { }
};


template<typename HANDLERS = default_button_handler,
         unsigned long BOUNCE_MS = 5,
         unsigned long HOLD_MS = 500>
struct button : public HANDLERS {

    using HANDLERS::HANDLERS;

    bool up() const { return !down_; }
    bool down() const { return down_; }

    bool hold() const { return hold_; }

    bool update(bool down, unsigned long t) {
        if (down != down_) {
            down_ = down;
            bounce_ = true;
            state_change_time_ = t;
        }

        if (!bounce_) {
            if (down_ && !hold_ &&
                t - state_change_time_ >= HOLD_MS)
            {
                hold_ = true;
                this->on_hold(t);
            }

            return false;
        }

        if (t - state_change_time_ >= BOUNCE_MS) {
            bounce_ = false;
            state_change_time_ = t;
            if (down_debounced_ != down_) {
                down_debounced_ = down_;
                this->on_down(down_, t);

                hold_ = false;

                return true;
            }
        }

        return false;
    }

private:
    bool down_ = false;
    bool down_debounced_ = false;
    bool bounce_ = false;
    bool hold_ = false;

    unsigned long state_change_time_ = 0;
};

}
