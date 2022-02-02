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
 * api_config_t: contains hte parameters to config the API
 */

#ifndef __API_CONFIG_T
    #define __API_CONFIG_T

#include <wayuu/wayuu.h>

typedef struct api_config_t
{
    int wayuu_service_port;
    char bind_addr[24];
    char log_file_name[ROOT_PATH_MAX];
    int engine_flags;
    bool engine_benchmark;
    char config_file_path[ROOT_PATH_MAX];
} api_config_t;

extern api_config_t api_config;


void api_config_default(void);
#endif
