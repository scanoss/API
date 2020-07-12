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
/**
 * log.h
 * 
 * A minimal logging facility.
 */
#ifndef __LOG_H
#define __LOG_H

#include <stdbool.h>

// Log file for analytics
#define WAYUU_ANALYTICS_LOG "/var/log/wayuu-access.log"

enum
{
  LOG_TRACE,
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_FATAL
};

#define log_trace(...) __logger(LOG_TRACE, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_debug(...) __logger(LOG_DEBUG, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_info(...) __logger(LOG_INFO, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_warn(...) __logger(LOG_WARN, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_error(...) __logger(LOG_ERROR, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define log_fatal(...) __logger(LOG_FATAL, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

void __logger(int level, const char *file, int line, const char *func, const char *format, ...);
void wayuu_failed();
void log_set_level(int level);
bool log_level_is_enabled(int level);
/**
 * log_set_file: Configures the main log file. Do it only once.
 */
void log_set_file(char *filename);
void log_close_file();

/**
 * Formats UTC timestamp in common log format.
 */
char *format_ts_common_log();

#endif
