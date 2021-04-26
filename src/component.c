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
#include <wayuu/wayuu.h>

#define CONTENTS_CMD "scanoss -k %s"
#define OBLIGATIONS_CMD "scanoss -l %s"


void ossfile_request_handler(api_request *req)
{
  char *md5 = extract_qs_value(req->form, "md5", 64);
  if (md5 == NULL)
  {
    bad_request(req);
    return;
  }
  char *command;
  asprintf(&command, CONTENTS_CMD, md5);
  log_debug("Executing %s", command);
  FILE *fp = popen(command, "r");
  if (fp == NULL)
  {
    log_error("Execution failed when obtaining contents of file with MD5: %s", md5);
    pclose(fp);
    not_found(req);
    return;
  }

  free(command);
  char buf[1024];

  // Send HTTP Headers
  if (fgets(buf, sizeof(buf) - 1, fp) == NULL || buf[0] == 'f' || strlen(buf) == 0)
  {
    log_warn("engine returned error exit status or empty: %s", buf);
    not_found(req);
    pclose(fp);
    return;
  }

  int len = return_headers_with_mime(req, 200, "text/plain");
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
  log_debug("Command executed without fails%s");
}



void license_obligations_request_handler(api_request *req)
{
  char *license_name = extract_qs_value(req->form, "license_name", MAX_LINE_LEN);
  if (license_name == NULL)
  {
    bad_request(req);
    return;
  }

  char *command;
  asprintf(&command, OBLIGATIONS_CMD, license_name);
  free(license_name);

  log_debug("Executing %s", command);
  FILE *fp = popen(command, "r");
  if (fp == NULL)
  {
    log_error("Execution failed when obtaining obligation for a license: %s", command);
    free(command);
    pclose(fp);
    not_found(req);
    return;
  }

  free(command);
  char buf[1024];

  // Send HTTP Headers
  if (fgets(buf, sizeof(buf) - 1, fp) == NULL || buf[0] == 'f' || strlen(buf) == 0)
  {
    log_warn("engine returned error exit status or empty: %s", buf);
    not_found(req);
    pclose(fp);
    return;
  }

  int len = return_headers_with_mime(req, 200, "text/plain");
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
  log_debug("Command executed without fails%s");
}