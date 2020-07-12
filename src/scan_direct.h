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
#ifndef __SCANOSS_SCAN_DIRECT_H
#define __SCANOSS_SCAN_DIRECT_H

#include "../wayuu/wayuu.h"

#define SCAN_FILE_MAX_SIZE 1024
#define SCAN_DIRECT_LINE_SIZE 1024

#define SCANOSS_CMD_SCAN_DIRECT_TMPL "/usr/bin/scanoss --force-wfp --%s %s %s"
#define SCANOSS_CMD_SCAN_DIRECT_PLAIN_TMPL "/usr/bin/scanoss --force-wfp %s"



void scan_direct_scan_request_handler(api_request *req);

/**
 * scan_direct_scan: Scans a wfp file and returns the result.
 * It returns output or NULL if there was a problem with the scanner
 */
void scan_direct_scan(api_request *req, char *path, char *assets, char *scantype);
#endif