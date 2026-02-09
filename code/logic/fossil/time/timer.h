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

typedef struct {
    uint64_t start_ns;
} fossil_time_timer_t;

void fossil_time_timer_start(fossil_time_timer_t *t);
uint64_t fossil_time_timer_elapsed_ns(const fossil_time_timer_t *t);
double fossil_time_timer_elapsed_ms(const fossil_time_timer_t *t);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
namespace fossil {
namespace time {

class Timer {
public:
    uint64_t start_ns;

    Timer();
    void start();
    uint64_t elapsed_ns() const;
    double elapsed_ms() const;
};

} // namespace time
} // namespace fossil
#endif

#endif
