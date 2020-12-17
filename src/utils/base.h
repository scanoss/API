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
// This header file includes all the other header files for convenience.
#ifndef __SCANOSS_BASE_H
#define __SCANOSS_BASE_H


#include "../external/crc32c/crc32c.h"
#include "file_utils.h"
#include "constants.h"
#include "string_utils.h"
#include "wfp_utils.h"


#define MAX_PATH 4096

// Vectorize function
#define Fn_apply(type, fn, ...)                                         \
  {                                                                     \
    void *stopper_for_apply = (int[]){0};                               \
    type **list_for_apply = (type *[]){__VA_ARGS__, stopper_for_apply}; \
    for (int i = 0; list_for_apply[i] != stopper_for_apply; i++)        \
      fn(list_for_apply[i]);                                            \
  }
// Free a list of pointers.
#define Free_all(...) Fn_apply(void, free, __VA_ARGS__);

#endif