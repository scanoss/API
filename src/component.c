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
#define _GNU_SOURCE
#include <string.h>
#include "./utils/string_utils.h"
#include "component.h"
#include "../wayuu/wayuu.h"

#define UNMZ_COMMAND "unmz -p /var/lib/ldb/mz -k %s"

void ossfile_request_handler(api_request *req)
{
  char *md5 = extract_qs_value(req->form, "md5", 64);
  if (md5 == NULL)
  {
    bad_request(req);
    return;
  }
  char *command;
  asprintf(&command, UNMZ_COMMAND, md5);
  log_debug("Executing %s\n", command);
  FILE *fp = popen(command, "r");
  if (fp == NULL)
  {
    log_error("Execution failed when obtaining contents of file with MD5: %s", md5);
    pclose(fp);
    not_found(req);
    return;
  }

  char buf[1024];

  // Send HTTP Headers
  fgets(buf, sizeof(buf) - 1, fp);
  if (buf == NULL || buf[0] == 'f')
  {
    log_warn("unmz returned exit status: %s", buf);
    send_http_status(req, 500, buf);
    pclose(fp);
    return;
  }

  int len = return_json_headers(req, 200);
  send_empty_line(req);
  len += 2;
  // Very important to print what we have already read from the file.
  http_print_str(req, buf);
  len += strlen(buf);
  // Send the rest until the end.
  len += send_stream(req, fp);
  pclose(fp);
  req->response_length = len;
  log_access(req, 200);
  log_debug("Finished returning file with MD5 %s", md5);
  free(command);
}
