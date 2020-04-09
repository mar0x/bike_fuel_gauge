#include "artl/button.h"
#include "artl/digital_out.h"
#include "artl/digital_in.h"
#include "artl/timer.h"
#include "artl/yield.h"

#include <EEPROM.h>

enum {
    CANCEL_TIMEOUT = 15000, // 15 sec

    CFG_BLINK_ON_TIMEOUT = 200,
    CFG_BLINK_OFF_TIMEOUT = 100,

    STORE_BLINK_TIMEOUT = 500,
    STORE_BLINK_ON_TIMEOUT = 50,
    STORE_BLINK_OFF_TIMEOUT = 50,
};

enum {
    MODE_NORMAL,
    MODE_CFG,
};

using led1 = artl::digital_out<3>;
using led2 = artl::digital_out<4>;
using led3 = artl::digital_out<5>;
using led4 = artl::digital_out<6>;
using led5 = artl::digital_out<7>;
using led6 = artl::digital_out<8>;
using led7 = artl::digital_out<9>;
using led8 = artl::digital_out<14>;
using led9 = artl::digital_out<15>;
using led10 = artl::digital_out<A0>;

using b_empty = artl::digital_in<10>;
using b_full = artl::digital_in<16>;

unsigned long last_update = 0;
int last_val = 0;
uint8_t last_led = 0;

struct config {

    void read() {
        EEPROM.get(0, *this);

        if (full_ == 0) full_ = 900;
        if (full_ <= empty_) full_ = empty_ + 1;
    }

    void store() const {
        EEPROM.put(0, *this);
    }

    void empty(uint16_t v) {
        empty_ = v;
        if (full_ <= empty_) full_ = empty_ + 1;
    }

    void full(uint16_t v) {
        full_ = v;
        if (full_ <= empty_) full_ = empty_ + 1;
    }

    uint16_t led(uint16_t v) const {
        if (v <= empty_) { return 0; }
        if (v >= full_) { return 9; }

        return 1 + (v - empty_) * 9 / (full_ - empty_);
    }

private:
    uint16_t empty_ = 0;
    uint16_t full_ = 900;
};

config cfg;

struct empty_handler {
    void on_down(bool, unsigned long) { }
    void on_hold(unsigned long);
};

struct full_handler {
    void on_down(bool, unsigned long) { }
    void on_hold(unsigned long);
};

artl::button<empty_handler> empty_btn;
artl::button<full_handler> full_btn;

struct led_blink_handler {
    void operator()(unsigned long);

protected:
    unsigned long on_time_;
    unsigned long off_time_;
    uint8_t on_;
};

struct cancel_handler {
    void operator()(unsigned long);
};

struct store_blink_handler {
    void operator()(unsigned long);
};

struct led_blink_timer_t : public artl::timer<led_blink_handler> {
    void start(unsigned long on_time, unsigned long off_time, unsigned long t);
};

led_blink_timer_t led_blink_timer;
artl::timer<cancel_handler> cancel_timer;
artl::timer<store_blink_handler> store_blink_timer;

uint8_t mode = MODE_NORMAL;

void setup() {
    led1().setup();
    led2().setup();
    led3().setup();
    led4().setup();
    led5().setup();
    led6().setup();
    led7().setup();
    led8().setup();
    led9().setup();
    led10().setup();

    led1().high();

    cfg.read();

    Serial.begin(115200);

    artl::yield();
}

void led(uint8_t l) {
    switch (l) {
    case 0: led2().low(); // fall through
    case 1: led3().low(); // fall through
    case 2: led4().low(); // fall through
    case 3: led5().low(); // fall through
    case 4: led6().low(); // fall through
    case 5: led7().low(); // fall through
    case 6: led8().low(); // fall through
    case 7: led9().low(); // fall through
    case 8: led10().low(); // fall through
    }

    switch (l) {
    case 9: led10().high(); // fall through
    case 8: led9().high(); // fall through
    case 7: led8().high(); // fall through
    case 6: led7().high(); // fall through
    case 5: led6().high(); // fall through
    case 4: led5().high(); // fall through
    case 3: led4().high(); // fall through
    case 2: led3().high(); // fall through
    case 1: led2().high(); // fall through
    }
}

void update_led(uint16_t v) {
    last_led = cfg.led(v);

    if (mode == MODE_NORMAL) {
        led(last_led);
    }
}

void start_cfg(unsigned long t) {
    mode = MODE_CFG;

    cancel_timer.schedule(t + CANCEL_TIMEOUT);
    store_blink_timer.cancel();
    led_blink_timer.start(CFG_BLINK_ON_TIMEOUT, CFG_BLINK_OFF_TIMEOUT, t);
}

void store_cfg(unsigned long t) {
    cfg.store();

    cancel_timer.cancel();

    led_blink_timer.start(STORE_BLINK_ON_TIMEOUT, STORE_BLINK_OFF_TIMEOUT, t);
    store_blink_timer.schedule(t + STORE_BLINK_TIMEOUT);

    mode = MODE_NORMAL;
}

void cancel_cfg(unsigned long) {
    cfg.read();

    cancel_timer.cancel();
    led_blink_timer.cancel();

    mode = MODE_NORMAL;

    led1().high();
    led(last_led);
}

void loop() {
    unsigned long t = millis();

    if (t - last_update > 100) {
        last_update = t;

        int v = analogRead(A1);
        last_val = v;

        update_led(v);

        Serial.println(v);
    }

    empty_btn.update(b_empty().read() == 0, t);
    full_btn.update(b_full().read() == 0, t);

    led_blink_timer.update(t);
    cancel_timer.update(t);
    store_blink_timer.update(t);

    artl::yield();
}

void empty_handler::on_hold(unsigned long t) {
    if (full_btn.hold()) {
        if (mode == MODE_NORMAL) {
            start_cfg(t);
            return;
        }

        if (mode == MODE_CFG) {
            store_cfg(t);
            return;
        }

        return;
    }

    if (full_btn.down()) { return; }

    if (mode == MODE_CFG) {
        cfg.read();
        cfg.empty(last_val);

        cancel_timer.schedule(t + CANCEL_TIMEOUT);

        led_blink_timer.start(STORE_BLINK_ON_TIMEOUT, STORE_BLINK_OFF_TIMEOUT, t);
        store_blink_timer.schedule(t + STORE_BLINK_TIMEOUT);
        return;
    }
}

void full_handler::on_hold(unsigned long t) {
    if (empty_btn.hold()) {
        if (mode == MODE_NORMAL) {
            start_cfg(t);
            return;
        }

        if (mode == MODE_CFG) {
            store_cfg(t);
            return;
        }

        return;
    }

    if (empty_btn.down()) { return; }

    if (mode == MODE_CFG) {
        cfg.read();
        cfg.full(last_val);

        cancel_timer.schedule(t + CANCEL_TIMEOUT);

        led_blink_timer.start(STORE_BLINK_ON_TIMEOUT, STORE_BLINK_OFF_TIMEOUT, t);
        store_blink_timer.schedule(t + STORE_BLINK_TIMEOUT);
        return;
    }
}

void led_blink_handler::operator()(unsigned long t) {
    if (on_) {
        led1().low();
        led(0);
        led_blink_timer.schedule(t + off_time_);
        on_ = 0;
    } else {
        led1().high();
        led(last_led);
        led_blink_timer.schedule(t + on_time_);
        on_ = 1;
    }
}

void cancel_handler::operator()(unsigned long t) {
    cancel_cfg(t);
}

void store_blink_handler::operator()(unsigned long t) {
    led_blink_timer.cancel();

    if (mode == MODE_NORMAL) {
        led1().high();
        led(last_led);
    }

    if (mode == MODE_CFG) {
        led_blink_timer.start(CFG_BLINK_ON_TIMEOUT, CFG_BLINK_OFF_TIMEOUT, t);
    }
}

void led_blink_timer_t::start(unsigned long on_time, unsigned long off_time,
    unsigned long t)
{
    on_time_ = on_time;
    off_time_ = off_time;

    on_ = 0;

    (*this)(t);
}

