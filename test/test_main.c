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
#ifdef SNOW_ENABLED

#ifndef __SCANOSS_TEST_MAIN_C
#define __SCANOSS_TEST_MAIN_C

#include "snow.h"
#include "../base/log.h"
#include "../src/utils/constants.h"

snow_main_decls;
int main(int argc, char **argv)
{
  log_set_level(LOG_DEBUG);
  // Initialize default paths for test.
  strcpy(WAYUU_WS_ROOT, DEFAULT_API_ROOT);
  

  return snow_main_function(argc, argv);
}

#endif
#endif
