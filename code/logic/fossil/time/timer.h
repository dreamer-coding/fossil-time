/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_TIME_TIMER_H
#define FOSSIL_TIME_TIMER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================
 * Fossil Time — Monotonic Timer
 * ====================================================== */

/*
 * Timer represents a monotonic measurement point.
 * It is NOT wall-clock time and must never jump backwards.
 */
typedef struct fossil_time_timer_t {
    uint64_t start_ns;
} fossil_time_timer_t;

/* ======================================================
 * C API — Core
 * ====================================================== */

/* Initialize / reset timer */
void fossil_time_timer_start(
    fossil_time_timer_t *timer
);

/* Elapsed time since start */
uint64_t fossil_time_timer_elapsed_ns(
    const fossil_time_timer_t *timer
);

uint64_t fossil_time_timer_elapsed_us(
    const fossil_time_timer_t *timer
);

uint64_t fossil_time_timer_elapsed_ms(
    const fossil_time_timer_t *timer
);

double fossil_time_timer_elapsed_sec(
    const fossil_time_timer_t *timer
);

/* ======================================================
 * C API — Convenience
 * ====================================================== */

/*
 * Measure elapsed time and reset start point.
 * Useful for frame timing, ticks, loops.
 */
uint64_t fossil_time_timer_lap_ns(
    fossil_time_timer_t *timer
);

/* ======================================================
 * C API — AI / Hint-Based Timing
 * ====================================================== */

/*
 * Interpret a timing hint and return a duration in nanoseconds.
 *
 * hint_id examples:
 *   "frame"        -> ~16ms
 *   "tick"         -> small scheduler quantum
 *   "yield"        -> minimal pause
 *   "human_short"  -> ~250ms
 *   "human_long"   -> ~2s
 */
uint64_t fossil_time_timer_hint_ns(
    const char *hint_id
);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* ======================================================
 * C++ Wrapper — Thin, Inline, ABI-Safe
 * ====================================================== */

#ifdef __cplusplus
namespace fossil {
namespace time {

class Timer {
public:
    fossil_time_timer_t raw;

    Timer() { }

    inline void start() {
        fossil_time_timer_start(&raw);
    }

    inline uint64_t elapsed_ns() const {
        return fossil_time_timer_elapsed_ns(&raw);
    }

    inline uint64_t elapsed_us() const {
        return fossil_time_timer_elapsed_us(&raw);
    }

    inline uint64_t elapsed_ms() const {
        return fossil_time_timer_elapsed_ms(&raw);
    }

    inline double elapsed_sec() const {
        return fossil_time_timer_elapsed_sec(&raw);
    }

    inline uint64_t lap_ns() {
        return fossil_time_timer_lap_ns(&raw);
    }

    static inline uint64_t hint_ns(const char *hint_id) {
        return fossil_time_timer_hint_ns(hint_id);
    }
};

} /* namespace time */
} /* namespace fossil */
#endif

#endif /* FOSSIL_TIME_TIMER_H */
