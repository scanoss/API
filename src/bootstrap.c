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
 * bootstrap.c 
 * 
 * Default implementation of bootstrapping functions.
 */

/**
  * @file bootstrap.c
  * @date 8 March 2021 
  * @brief API router. Each request is routed to the appropriate function.
  */

#include <stdlib.h>
#include "scan_direct.h"
#include "component.h"
#include "bootstrap.h"
#include "attribution.h"

/**
 * @brief  Each verb and URI is mapped to a handler function.
 */

static void bootstrap_api_routes()
{
  router_add_route("POST:/scan/direct", scan_direct_scan_request_handler, NULL);
  router_add_route("GET:/file_contents/{md5}", ossfile_request_handler, NULL);
  router_add_route("POST:/sbom/attribution", attribution_request_handler, NULL);
  router_add_route("GET:/license/obligations/{license_name}", license_obligations_request_handler, NULL);
}

/**
 * @brief It is called when from main.c after the API is configured.
 */

void bootstrap_api()
{
    bootstrap_api_routes();
}
