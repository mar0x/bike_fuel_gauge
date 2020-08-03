
#pragma once

struct filter_t {

    unsigned long update(unsigned long v, unsigned long t) {
        last_update = t;

        hist_push(v);

        if (t == 0) {
            for (uint8_t i = 0; i < 4; i++) {
                hist_push(v);
            }

            mean_ = v;
            cov_ = 0.0;

            value = v;
        } else {
            mean_ = mean();
            cov_ = cov(mean_);

            if (cov_ < 0.05) {
                value = (unsigned long) mean_;
            }
        }

        return value;
    }

    void hist_push(unsigned long v) {
        hist_ring[hist_id] = v;
        hist_id = (hist_id + 1) % HIST_SIZE;
    }

    operator unsigned long() const { return value; }

    double mean() const {
        double s = 0;

        for (uint8_t i = 0; i < HIST_SIZE; i++) {
            s += hist_ring[i];
        }

        return s / (double) HIST_SIZE;
    }

    double cov(double m) const {
        double variance = 0;

        for (uint8_t i = 0; i < HIST_SIZE; i++) {
            double v = hist_ring[i];
            v -= m;
            variance += v * v;
        }

        return sqrt(variance) / m;
    }

    double mean_;
    double cov_;

private:

    enum {
        HIST_SIZE = 5,
    };

    unsigned long value = 0;
    unsigned long last_update = 0;
    unsigned long hist_ring[HIST_SIZE] = {0, 0, 0, 0, 0};
    uint8_t hist_id = 0;
};
