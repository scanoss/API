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
#ifndef __SCANOSS_COMPONENT_H
#define __SCANOSS_COMPONENT_H

#include <wayuu/router.h>

/**
 * @openapi-method
 * operationId: ossfile
 * request: GET /file_contents/{MD5}
 * description: Return the contents of the file with the given MD5 checksum. 
 * tags: inventory
 * params:
 * - name: MD5
 *   place: path
 *   type: string
 *   required: true
 *   description: "The MD5 checksum of the file"
 * responses:
 * - status: 200 
 *   description: "Return contents of the file"
 *   content: text/plain
 *   schema: string
 * - status: 404
 *   description: "File not found"
 */
void ossfile_request_handler(api_request *req);

#endif