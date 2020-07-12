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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../wayuu/wayuu.h"
#include "utils/base.h"
#include "bootstrap.h"

#define SCANOSS_API_LOG "/var/log/scanoss-api.log"

int main(int argc, char *argv[])
{
	log_set_file(SCANOSS_API_LOG);
	int ws_port = DEFAULT_PORT;
	strcpy(WAYUU_WS_ROOT, DEFAULT_API_ROOT);
	char bind_addr[24] = "127.0.0.1";
	signal(SIGPIPE, SIG_IGN);

	// Parse CLI Arguments using getopt

	int opt;

	while ((opt = getopt(argc, argv, ":b:p:r:hd")) != -1)
	{
		switch (opt)
		{

		case 'd':
			log_set_level(LOG_DEBUG);
			break;
		case 'h':
			printf("USAGE: scanossws [-d] [-b ip_addr] [-p port] [-r root]\n");
			exit(0);
			break;
		case 'p':
			ws_port = atoi(optarg);
			break;
		case 'b':
			strcpy(bind_addr, optarg);
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


	// API Bootstrapping logic.
	bootstrap_api();

	ws_launch(ws_port, bind_addr);
	log_close_file();
	exit(0);
}



