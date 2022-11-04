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

api_config_t api_config;


 /**
 * @brief read a file and put it into a buffer.
 * @param[out] out output buffer.
 * @param path file path.
 * @param maxlen max length to read.
 */
static char * read_config_file(char * path)
{
	char *src = NULL;
	uint64_t length = 0;

	if (!is_file(path))
	{
		return NULL;
	}

	FILE *file = fopen(path, "rb");
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
	memset(&api_config, 0, sizeof(api_config));
    strcpy(api_config.config_file_path, DEFAULT_API_CONFIG_PATH);
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
#define CONFIG_FILE_KEY_ENGINE_FLAGS "\"engine_flags\": "
#define CONFIG_FILE_KEY_LOG_PATH "\"log_file_path\": \""
#define CONFIG_FILE_KEY_ENGINE_BENCHMARK "\"engine_benchmark\": \""
#define CONFIG_FILE_KEY_BIND_ADDRESS "\"bind_address\": \""
#define CONFIG_FILE_KEY_PORT "\"port\": "

bool api_config_read_file(char *  path)
{
	api_config_t m_api_config;
	
	/*copy the default config */
	memcpy(&m_api_config, &api_config, sizeof(api_config));
	
	char * json = read_config_file(path);
	char field[1024];
	char * end = NULL;
	
	if (!json)
        return false;
	
	memset(m_api_config.config_file_path, 0, sizeof(m_api_config.config_file_path));
	strcpy(m_api_config.config_file_path, path);

	char * key_engine_flags = strstr(json, CONFIG_FILE_KEY_ENGINE_FLAGS);
	if (key_engine_flags)
	{
		key_engine_flags += strlen(CONFIG_FILE_KEY_ENGINE_FLAGS);
		m_api_config.engine_flags = atoi(key_engine_flags);
		printf("Engine flags result: %d \n", m_api_config.engine_flags);
	}

	char * key_engine_benchmark = strstr(json, CONFIG_FILE_KEY_ENGINE_BENCHMARK);
	if (key_engine_benchmark)
	{
		key_engine_benchmark += strlen(CONFIG_FILE_KEY_ENGINE_BENCHMARK);
		end = strchr(key_engine_benchmark, '"');
		if (end)
			strncpy(field, key_engine_benchmark, end - key_engine_benchmark);
		else
			return false;
		
		if (strstr(key_engine_benchmark, "true"))
			m_api_config.engine_benchmark = true;
		printf("benchmark result: %d\n", m_api_config.engine_benchmark);
	}

	char * key_bind_adress = strstr(json, CONFIG_FILE_KEY_BIND_ADDRESS);
	if (key_bind_adress)
	{
		key_bind_adress += strlen(CONFIG_FILE_KEY_BIND_ADDRESS);
		end = strchr(key_bind_adress, '"');
		if (end)
		{
			memset(m_api_config.bind_addr, 0, sizeof(m_api_config.bind_addr));
			strncpy(m_api_config.bind_addr, key_bind_adress, end - key_bind_adress);
		}
		else
			return false;

		printf("Bind address result: %s\n", m_api_config.bind_addr);
	}

	char * key_log_path = strstr(json, CONFIG_FILE_KEY_LOG_PATH);
	if (key_log_path)
	{
		key_log_path += strlen(CONFIG_FILE_KEY_LOG_PATH);
		end = strchr(key_log_path, '"');
		if (end)
		{
			memset(m_api_config.log_file_name, 0, sizeof(m_api_config.log_file_name));
			strncpy(m_api_config.log_file_name, key_log_path, end - key_log_path);
		}
		else
			return false;

		printf("log path result: %s\n", m_api_config.log_file_name);
	}

	char * key_port = strstr(json, CONFIG_FILE_KEY_PORT);
	if (key_port)
	{
		key_port += strlen(CONFIG_FILE_KEY_PORT);
		m_api_config.wayuu_service_port = atoi(key_port);
		printf("Port result: %d\n", m_api_config.wayuu_service_port);
	}

	/* If all is OK replace the default with the updated config */
	memcpy(&api_config, &m_api_config, sizeof(api_config));

	return true;

}