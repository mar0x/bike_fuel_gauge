
#pragma once

struct serial_cmd_t {

    enum {
        CMD_UNKNOWN,
        CMD_STATE,
        CMD_FUEL_SENSOR,
        CMD_BRIGHTNESS,
        CMD_LIGHT_SENSOR,
        CMD_COLOR_SCHEME,
        CMD_GRID,
        CMD_LED_COLOR,
        CMD_DEBUG_LEVEL,
        CMD_FACTORY_RESET,
        CMD_VERSION,
        CMD_HELP,

        MAX_SIZE = 50,
        MAX_ARGS = 5,
    };

    serial_cmd_t() : ready_(false), size_(0), command_(CMD_UNKNOWN) { }

    void read(uint8_t b);

    operator bool() const { return ready_; }

    void reset() {
        ready_ = false;
        size_ = 0;
        command_ = CMD_UNKNOWN;
    }

    uint8_t command() const { return command_; }

    template<typename T>
    bool get_hex(uint8_t s, uint8_t e, T& v) {
        for (uint8_t p = s; p < e; ++p) {
            char c = buf_[p];

            if (c >= '0' && c <= '9') {
                v = v * 16 + (c - '0');
                continue;
            }

            if (c >= 'a' && c <= 'f') {
                v = v * 16 + (10 + c - 'a');
                continue;
            }

            if (c >= 'A' && c <= 'F') {
                v = v * 16 + (10 + c - 'A');
                continue;
            }

            return false;
        }

        return true;
    }

    template<typename T>
    bool get_dec(uint8_t s, uint8_t e, T& v) {
        for (uint8_t p = s; p < e; ++p) {
            if (buf_[p] >= '0' && buf_[p] <= '9') {
                v = v * 10 + (buf_[p] - '0');
            } else {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    bool get_bin(uint8_t s, uint8_t e, T& v) {
        for (uint8_t p = s; p < e; ++p) {
            if (buf_[p] >= '0' && buf_[p] <= '1') {
                v = (v << 1) + (buf_[p] - '0');
            } else {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    bool get_num(uint8_t n, T& v) {
        if (n >= arg_size_) {
            return false;
        }

        arg *a = &arg_[n];

        v = 0;

        if (a->end - a->start > 2) {
            if (buf_[a->start] == '0' && (buf_[a->start + 1] == 'x' || buf_[a->start + 1] == 'X')) {
                return get_hex(a->start + 2, a->end, v);
            }
        }

        if (a->end - a->start > 1) {
            if (buf_[a->end - 1] == 'h' || buf_[a->end - 1] == 'H') {
                return get_hex(a->start, a->end - 1, v);
            }

            if (buf_[a->end - 1] == 'b' || buf_[a->end - 1] == 'B') {
                return get_bin(a->start, a->end - 1, v);
            }
        }

        n = 1;

        for (uint8_t p = a->start; p < a->end; ++p) {
            if (buf_[p] >= '0' && buf_[p] <= '1') {
                v = v + ((buf_[p] - '0') ? n : 0);
                n = n << 1;
            } else {
                v = 0;
                break;
            }

            ++p;
            if (p >= a->end) return true;

            if (buf_[p] != ',') {
                v = 0;
                break;
            }
        }

        return get_dec(a->start, a->end, v);
    }

    bool get_arg(uint8_t n, uint8_t& v) {
        return get_num(n, v);
    }

    bool get_arg(uint8_t n, uint16_t& v) {
        return get_num(n, v);
    }

    bool get_arg(uint8_t n, unsigned long& v) {
        return get_num(n, v);
    }

    template<typename T>
    bool get_arg(uint8_t n, T& v) {
        if (n >= arg_size_) {
            return false;
        }

        uint8_t l = arg_[n].end - arg_[n].start;
        uint8_t c = (l > sizeof(T)) ? sizeof(T) : l;

        memcpy(&v, &buf_[arg_[n].start], c);

        if (l < sizeof(T)) {
            memset(((uint8_t *) &v) + l, ' ', sizeof(T) - l);
        }

        return true;
    }

    template<typename T, typename ...Args>
    bool get_arg(uint8_t n, T& v, Args&& ... args) {
        return get_arg(n, v) && get_arg(n + 1, args...);
    }

//private:
    void parse();

    struct arg {
        uint8_t start;
        uint8_t end;
    };

    struct cmd_parse {
        uint8_t id;
        const char *cmd;
        uint8_t cmd_len;
    };

    static const cmd_parse cmds[];

    char buf_[MAX_SIZE];
    bool ready_;
    uint8_t size_;
    uint8_t command_;

    arg arg_[MAX_ARGS];
    uint8_t arg_size_;
};

inline void
serial_cmd_t::read(uint8_t b) {
    if (b == '\n' || b == '\r') {
        buf_[size_] = 0;

        parse();
        ready_ = true;

        return;
    }

    if (size_ >= MAX_SIZE) {
        return;
    }

    buf_[size_++] = b;
}


const serial_cmd_t::cmd_parse serial_cmd_t::cmds[] = {
    { CMD_STATE, "ST", 2 },
    { CMD_FUEL_SENSOR, "FS", 2 },
    { CMD_BRIGHTNESS, "BR", 2 },
    { CMD_LIGHT_SENSOR, "LS", 2 },
    { CMD_COLOR_SCHEME, "CS", 2 },
    { CMD_GRID, "GR", 2 },
    { CMD_DEBUG_LEVEL, "DL", 2 },
    { CMD_LED_COLOR, "LC", 2 },
    { CMD_FACTORY_RESET, "FR", 2 },
    { CMD_VERSION, "V", 1 },
    { CMD_HELP, "?", 1 },
    { CMD_UNKNOWN, "", 0 },
};

inline void
serial_cmd_t::parse() {
    arg_size_ = 0;
    arg *a = &arg_[0];
    char in_quote = 0;

    a->start = 0;

    for (uint8_t i = 0; i < size_; i++) {
        char b = buf_[i];

        if (b == '"' && i == a->start) {
            a->start = i + 1;
            in_quote = b;
            continue;
        }

        if (in_quote && in_quote == b) {
            a->end = i;

            debug(7, "arg #", arg_size_, ", start ", a->start, ", end ", a->end);
            //log_window::println("arg #", arg_size_, ", start ", a->start, ", end ", a->end);

            arg_size_++;
            a++;

            a->start = i + 1;
            in_quote = 0;

            if (arg_size_ >= MAX_ARGS) {
                return;
            }
        }

        if (in_quote == 0 && (b == ' ' || b == '\t')) {
            if (i == a->start) {
                a->start = i + 1;
                continue;
            }

            a->end = i;

            //log_window::println("arg #", arg_size_, ", start ", a->start, ", end ", a->end);

            arg_size_++;
            a++;

            a->start = i + 1;

            if (arg_size_ >= MAX_ARGS) {
                return;
            }
        }
    }

    if (a->start < size_) {

        a->end = size_;

        //log_window::println("arg #", arg_size_, ", start ", a->start, ", end ", a->end);

        arg_size_++;
    }

    if (arg_size_ > 0) {
        a = &arg_[0];
        char *b = &buf_[a->start];

        for (uint8_t i = 0; cmds[i].id != CMD_UNKNOWN; ++i) {
            if (a->end - a->start != cmds[i].cmd_len) continue;

            uint8_t j = 0;

            for (; j < cmds[i].cmd_len; ++j) {
                if (b[j] != cmds[i].cmd[j]) { break; }
            }

            if (j == cmds[i].cmd_len) {
                command_ = cmds[i].id;
                break;
            }
        }
    }
}


static const char help[] PROGMEM = R"HELP(
ST [<s>] - state
FS [<v>] - fuel sensor value
BR [<b>] - brightness
CS [<s>] - color scheme
GR [<n> [<v]] - config grid

LS - light sensor
DL [<l>] - debug level
LC <n> <r> <g> <b> - led color

V - show version

FR <V> - factory reset
)HELP";
