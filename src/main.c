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
extern bool WAYUU_SSL_ON;

#define SCANOSS_API_LOG "/var/log/scanoss-api.log"
char log_file_name[ROOT_PATH_MAX];
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

int main(int argc, char *argv[])
{
	BENCHMARK_ENGINE = false;
	WAYUU_SSL_ON = true;
	if (getenv("SCANOSS_BENCHMARK_ENGINE"))
	{
		BENCHMARK_ENGINE = true;
	}
	//log_set_file(SCANOSS_API_LOG);
	int ws_port = DEFAULT_PORT;
	strcpy(WAYUU_WS_ROOT, DEFAULT_API_ROOT);
	strcpy(WWW_INDEX, DEFAULT_WWW_INDEX);
	strcpy(FAVICON_URL, DEFAULT_FAVICON_URL);
	char bind_addr[24] = "127.0.0.1";
	signal(SIGPIPE, SIG_IGN);
	strcpy(log_file_name,SCANOSS_API_LOG);
	// Parse CLI Arguments using getopt

	int opt;

	while ((opt = getopt(argc, argv, ":l:b:p:r:hdtf")) != -1)
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
			ws_port = atoi(optarg);
			break;
		case 'b':
			strcpy(bind_addr, optarg);
			break;
		case 'l':
			strcpy(log_file_name, optarg);
			break;
		case 'r':
			strcpy(WAYUU_WS_ROOT, optarg);
			log_info("SCANOSS API ROOT now: %s", WAYUU_WS_ROOT);
			if (!is_dir(WAYUU_WS_ROOT))
			{
				log_fatal("Unable to start, root directory doesn't exist: %s", WAYUU_WS_ROOT);
			}
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
	log_set_file(log_file_name);
	sprintf(WAYUU_STATIC_ROOT, "%s/%s", WAYUU_WS_ROOT, DEFAULT_STATIC_ROOT);

	// API Bootstrapping logic.
	bootstrap_api();

	ws_launch(ws_port, bind_addr);
	log_close_file();
	exit(0);
}
