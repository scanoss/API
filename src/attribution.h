// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 SCANOSS LTD
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
#ifndef __SCANOSS_ATRIBUTION_H
#define __SCANOSS_ATRIBUTION_H

#include <wayuu/router.h>
#define SCAN_FILE_MAX_SIZE 1024
#define SCAN_ATTRIBUTION_LINE_SIZE 1024

/**
 * @openapi-method
 * operationId: scanattribution
 * request: POST /sbom/attribution 
 * description: Return the attribution notices for a list of given components in a JSON SBOM format 
 * tags: sbom
 * params:
 * - name: file
 *   type: file
 *   place: query
 *   required: true
 *   description: "The name of the file containing the SBOM.json"
 * responses:
 * - status: 200 
 *   description: "Attribution notices for a given list of components in SBOM.json file"
 *   content: text/plain
 *   schema: string
 * - status: 404
 *   description: "File not found"
 */
void attribution_request_handler(api_request *req);
void attribution_scan(api_request *req, char *path);

#endif
