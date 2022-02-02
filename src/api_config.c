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
#include <string.h>
#include "api_config.h"

#define DEFAULT_BIND_ADDRESS "127.0.0.1"
#define DEFAULT_API_LOG "/var/log/scanoss-api.log"
#define DEFAULT_API_CONFIG_PATH "/var/scanoss/api-config.json"

api_config_t api_config;


 /**
 * @brief read a file and put it into a buffer.
 * @param[out] out output buffer.
 * @param path file path.
 * @param maxlen max length to read.
 */
static char * read_config_file()
{
	char *src = NULL;
	uint64_t length = 0;

	if (!is_file(api_config.config_file_path))
	{
		return NULL;
	}

	FILE *file = fopen(api_config.config_file_path, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file);
    		
    fseek(file, 0, SEEK_SET);
		src = calloc(length, 1);
		if (src)
		{
			fread(src, 1, length, file);
		}
		fclose(file);
	  return src;
	}

  return NULL;
}

void api_config_default(void)
{
    strcpy(api_config.bind_addr, DEFAULT_BIND_ADDRESS);
    strcpy(api_config.log_file_name, DEFAULT_API_LOG);
    api_config.wayuu_service_port = DEFAULT_PORT;
    api_config.engine_flags = 0;
    api_config.engine_benchmark = false;
}

/**
 * @brief Read flags from /etc/scanoss_flags.cfg
 * @return //TODO
 */
#define CONFIG_FILE_KEY_ENGINE "\"engine: \""
bool api_config_read_file()
{
	char * json = read_config_file();

    if (!json)
        return false;

    

}