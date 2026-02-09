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
#ifndef FOSSIL_TIME_SPAN_H
#define FOSSIL_TIME_SPAN_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================
 * Fossil Time — Span (Duration)
 * ====================================================== */

/*
 * Represents a duration, not anchored to a calendar.
 * All fields are optional and governed by precision_mask.
 */
typedef struct fossil_time_span_t {

    /* -------- Large units -------- */
    int64_t days;

    /* -------- Clock units -------- */
    int32_t hours;
    int32_t minutes;
    int32_t seconds;

    /* -------- Sub-second (SI ladder) -------- */
    int32_t milliseconds;
    int32_t microseconds;
    int32_t nanoseconds;
    int32_t picoseconds;
    int32_t femtoseconds;
    int32_t attoseconds;
    int32_t zeptoseconds;
    int32_t yoctoseconds;

    /* -------- Precision -------- */
    uint64_t precision_mask;

} fossil_time_span_t;

/* ======================================================
 * Precision Mask Bits
 * ====================================================== */

#define FOSSIL_TIME_SPAN_PRECISION_DAYS     (1ULL << 0)
#define FOSSIL_TIME_SPAN_PRECISION_HOURS    (1ULL << 1)
#define FOSSIL_TIME_SPAN_PRECISION_MINUTES  (1ULL << 2)
#define FOSSIL_TIME_SPAN_PRECISION_SECONDS  (1ULL << 3)

#define FOSSIL_TIME_SPAN_PRECISION_MILLI    (1ULL << 4)
#define FOSSIL_TIME_SPAN_PRECISION_MICRO    (1ULL << 5)
#define FOSSIL_TIME_SPAN_PRECISION_NANO     (1ULL << 6)
#define FOSSIL_TIME_SPAN_PRECISION_PICO     (1ULL << 7)
#define FOSSIL_TIME_SPAN_PRECISION_FEMTO    (1ULL << 8)
#define FOSSIL_TIME_SPAN_PRECISION_ATTO     (1ULL << 9)
#define FOSSIL_TIME_SPAN_PRECISION_ZEPTO    (1ULL << 10)
#define FOSSIL_TIME_SPAN_PRECISION_YOCTO    (1ULL << 11)

/* ======================================================
 * C API — Core
 * ====================================================== */

/* Zero / reset */
void fossil_time_span_clear(fossil_time_span_t *span);

/* Validation & normalization */
int  fossil_time_span_validate(const fossil_time_span_t *span);
void fossil_time_span_normalize(fossil_time_span_t *span);

/* ======================================================
 * C API — Construction
 * ====================================================== */

/*
 * Create span from value + unit string.
 *
 * unit_id examples:
 *   "days", "hours", "minutes", "seconds"
 *   "ms", "us", "ns", "ps", "fs", "as", "zs", "ys"
 */
void fossil_time_span_from_unit(
    fossil_time_span_t *span,
    int64_t value,
    const char *unit_id
);

/*
 * AI-friendly construction:
 *   "moment"
 *   "short"
 *   "long"
 *   "human_tick"
 *   "frame"
 */
void fossil_time_span_from_ai(
    fossil_time_span_t *span,
    const char *hint_id
);

/* ======================================================
 * C API — Arithmetic
 * ====================================================== */

void fossil_time_span_add(
    fossil_time_span_t *result,
    const fossil_time_span_t *a,
    const fossil_time_span_t *b
);

void fossil_time_span_sub(
    fossil_time_span_t *result,
    const fossil_time_span_t *a,
    const fossil_time_span_t *b
);

/* ======================================================
 * C API — Conversion
 * ====================================================== */

int64_t fossil_time_span_to_seconds(
    const fossil_time_span_t *span
);

int64_t fossil_time_span_to_nanoseconds(
    const fossil_time_span_t *span
);

/* ======================================================
 * C API — Formatting
 * ====================================================== */

/*
 * format_id examples:
 *   "short"     -> "5s"
 *   "human"     -> "5 seconds"
 *   "precise"   -> "5.000000000 s"
 *   "ai"
 */
int fossil_time_span_format(
    const fossil_time_span_t *span,
    char *buffer,
    size_t buffer_size,
    const char *format_id
);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* ======================================================
 * C++ Wrapper — Thin, Inline
 * ====================================================== */

#ifdef __cplusplus
namespace fossil {
namespace time {

class Span {
public:
    fossil_time_span_t raw;

    Span() { }

    inline void clear() {
        fossil_time_span_clear(&raw);
    }

    inline bool validate() const {
        return fossil_time_span_validate(&raw) != 0;
    }

    inline void normalize() {
        fossil_time_span_normalize(&raw);
    }

    inline void from_unit(int64_t value, const char *unit_id) {
        fossil_time_span_from_unit(&raw, value, unit_id);
    }

    inline void from_ai(const char *hint_id) {
        fossil_time_span_from_ai(&raw, hint_id);
    }

    inline int64_t to_seconds() const {
        return fossil_time_span_to_seconds(&raw);
    }

    inline int64_t to_nanoseconds() const {
        return fossil_time_span_to_nanoseconds(&raw);
    }

    inline int format(
        char *buffer,
        size_t buffer_size,
        const char *format_id
    ) const {
        return fossil_time_span_format(&raw, buffer, buffer_size, format_id);
    }

    static inline Span add(const Span &a, const Span &b) {
        Span out;
        fossil_time_span_add(&out.raw, &a.raw, &b.raw);
        return out;
    }

    static inline Span sub(const Span &a, const Span &b) {
        Span out;
        fossil_time_span_sub(&out.raw, &a.raw, &b.raw);
        return out;
    }
};

} /* namespace time */
} /* namespace fossil */
#endif

#endif /* FOSSIL_TIME_SPAN_H */
