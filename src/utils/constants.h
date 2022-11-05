// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2018-2020 SCANOSS LTD
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef __SCANOSS_CONSTANTS_H
#define __SCANOSS_CONSTANTS_H

#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

// APP VERSION
#define SCANOSS_API_VERSION "1.1.3"
#define DEFAULT_API_ROOT "/var/lib/scanoss"

#define MD5_SIZE 34
#define SCAN_RESULT_MAX_PATH 256
#define SCAN_RESULT_MAX_VENDOR 256
#define SCAN_RESULT_MAX_ARTIFACT 256
#define SCAN_RESULT_MAX_VERSION 64
#define SCAN_LOG_MAX_LENGTH 256
#define SCAN_LOG_TS_LENGTH 64

// Attribute limits
#define MAX_PROJECT_NAME 256
#define MAX_PROJECT_DESCRIPTION 4096
#define MAX_USERNAME 256
#define MAX_SCAN_CODE 256
#define MAX_POST_VALUE 65536

#define MAX_SCAN_STATUS 128
// Maximum length of a scan result.
#define MAX_SCAN_RESULT 1024

#define BENCHMARK_ENGINE_FILE "/tmp/scanoss_engine_benchmark.csv"

#endif // __SCANOSS_CONSTANTS_H
