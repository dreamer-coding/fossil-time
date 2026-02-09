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
#ifndef FOSSIL_TIME_SLEEP_H
#define FOSSIL_TIME_SLEEP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void fossil_time_sleep_ns(uint64_t nanoseconds);
void fossil_time_sleep_ms(uint32_t milliseconds);
void fossil_time_sleep_sec(uint32_t seconds);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
namespace fossil {
namespace time {

class Sleep {
public:
    static void ns(uint64_t nanoseconds);
    static void ms(uint32_t milliseconds);
    static void sec(uint32_t seconds);
};

} // namespace time
} // namespace fossil
#endif

#endif
