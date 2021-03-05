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
#include "utils/base.h"
#include "attribution.h"
#include "../wayuu/wayuu.h"

#define SCAN_AN_COMMAND "scanoss -a %s"
/**
@brief handle used by the router to scann attribution notices
@param req Struct that contains the request parameters 
*/
void attribution_request_handler(api_request *req)
{

	char *filename = extract_qs_value(req->form, "file", MAX_PATH);
	if (filename == NULL)
	{
	    log_debug("No file supplied returning bad request");
		bad_request(req);
	if (filename != NULL)
    {
      free(filename);
    }
    return;
  	}
	log_debug("Scanning SBOM file: %s", filename);
  
	// Extract the filename from the POST
	char *tmpfile = extract_qs_value(req->form, "tmpfile", SCAN_FILE_MAX_SIZE);
	if (!tmpfile || tmpfile[0] == 0)
	{
    	log_debug("Unable to find tmpfile, returning bad request");
    	bad_request(req);
    	return;
  	}
  
  	//get the absolute path of the temp file
  	char tmpfilepath[MAX_PATH];
	sprintf(tmpfilepath, "%s/%s", FILE_DOWNLOAD_TMP_DIR, tmpfile);
	attribution_scan(req, tmpfilepath);
	free(tmpfile);
}


/**
 * @brief get attribution notices for components given SBOM 
 * @description runs the command scanoss -a <SBOM.json> to collect the
 *  attibution notices of each component. The attibution notices of each
 *  component are returned to the client as response.
 *  An internal server error is the response for no results.
 */
void attribution_scan(api_request *req, char *path)
{
	char command[MAX_PATH];
	sprintf(command, SCAN_AN_COMMAND, path);
	log_debug("Executing %s\n", command);
	//Execute the command
	FILE *fp = popen(command, "r");
	if (fp == NULL)
	{
		log_error("Scan Execution failed for direct scan: %s", path);
		pclose(fp);
		return;
	}
	//	Capture the results
	char buf[SCAN_ATTRIBUTION_LINE_SIZE];

  // Send HTTP Headers
	fgets(buf, sizeof(buf) - 1, fp);
  
	if (buf == NULL || buf[0] == 'E')
	{
		log_warn("Scanner returned exit status: %s", buf);
		send_http_status(req, 500, buf);
    	pclose(fp);
		return;
	}
	//	Send header
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
	log_debug("Finished scanning %s", path);
}
