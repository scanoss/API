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
  * @file main.c
  * @date 20 July 2021 
  * @brief Contains a method to show the API menu to the user and a function to handle the user's input. 
  */

#include <execinfo.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <wayuu/wayuu.h>
#include "utils/base.h"
#include "bootstrap.h"
#include "utils/constants.h"

#include "api_config.h"

extern bool WAYUU_SSL_ON;

#define SCANOSS_API_LOG "/var/log/scanoss-api.log"
char log_file_name[ROOT_PATH_MAX];


 /**
 * @brief print options to stdout
 */


void print_usage(){
  printf("USAGE: scanossws [-f] [-d] [-t] [-b ip_addr] [-p port] [-r root]\n\n"); 
  printf("-t         : Enabled TRACE mode\n");
  printf("-d         : Enabled DEBUG mode\n");
  printf("-b ip_addr : Bind to IP address. Default: \"0.0.0.0\"\n");
  printf("-p port    : Bind to TCP port. Default: 4443\n");
  printf("-r root    : Use root as the root folder for WAYUU. Default: /etc/wayuu\n");
  printf("-f         : HTTP mode\n");
  printf("-l         : Specify log filename\n");	     	
  printf("-v         : Print version and exits\n");
}


 /**
 * @brief setting API from command line
 * @param argc number of arguments
 * @param argv vector of arguments
 */

int main(int argc, char *argv[])
{
	api_config_default();

	WAYUU_SSL_ON = true;
	if (getenv("SCANOSS_BENCHMARK_ENGINE"))
	{
		api_config.engine_benchmark = true;
	}

	strcpy(WAYUU_WS_ROOT, DEFAULT_API_ROOT);
	strcpy(WWW_INDEX, DEFAULT_WWW_INDEX);
	strcpy(FAVICON_URL, DEFAULT_FAVICON_URL);

	signal(SIGPIPE, SIG_IGN);

	// Parse CLI Arguments using getopt

	int opt;

	while ((opt = getopt(argc, argv, ":l:b:p:r:hdtfv")) != -1)
	{
		switch (opt)
		{
		
		case 'f':
			WAYUU_SSL_ON = false;
			break;
		case 'd':
			log_set_level(LOG_DEBUG);
			break;
		case 't':
			log_set_level(LOG_TRACE);
			break;
		case 'h':
			print_usage();
			exit(0);
			break;
		case 'p':
			api_config.wayuu_service_port = atoi(optarg);
			break;
		case 'b':
			strcpy(api_config.bind_addr, optarg);
			break;
		case 'l':
			strcpy(api_config.log_file_name, optarg);
			break;
		case 'r':
			strcpy(WAYUU_WS_ROOT, optarg);
			log_info("SCANOSS API ROOT now: %s", WAYUU_WS_ROOT);
			if (!is_dir(WAYUU_WS_ROOT))
			{
				log_fatal("Unable to start, root directory doesn't exist: %s", WAYUU_WS_ROOT);
			}
			break;
		case 'v':
			printf("SCANOSS API - Version: %s\n", SCANOSS_API_VERSION);
			exit(0);
			break;
		case ':':
			printf("option needs a value\n");
			break;
		case '?':
			printf("unknown option: %c\n", optopt);
			exit(1);
			break;
		}
	}
	
	log_set_file(api_config.log_file_name);
	sprintf(WAYUU_STATIC_ROOT, "%s/%s", WAYUU_WS_ROOT, DEFAULT_STATIC_ROOT);

	// API Bootstrapping logic.
	bootstrap_api();

	ws_launch(api_config.wayuu_service_port, api_config.bind_addr, NULL);
	log_close_file();
	exit(0);
}
