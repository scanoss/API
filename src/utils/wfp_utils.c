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

  /**
  * @file wfp_utils.c
  * @date 3 March 2021 
  * @brief Contains functions to process a wfp file and get number of files contained in it.
  */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "wfp_utils.h"
#include <wayuu/wayuu.h>

// Size of the read buffer, 1Mb
#define WFP_BUFFER_SIZE 1024 * 1024
#define WFP_FILE_KEY "file="

/**
 * @brief Counts the number of files in string. 
 * @param buffer The string to count the number of files in.
 * @return return the number of files in the string. Returns 0 if the buffer is empty or equal to 0.
 */

int wfp_count_files_in_string(char *buffer)
{
  if (!buffer || strlen(buffer) == 0)
  {
    return 0;
  }
  int nfiles = 0;
  int cur_line_len = 0;
  int total_len = 0;

  char *string = strdup(buffer);
  char *tmp = string;
  while (*string)
  {
    // Find end of line
    cur_line_len++;
    total_len++;
    string++;
    if (*string == '\n')
    {
      *string = 0;
      if (strstr(string - cur_line_len, "file=") != NULL)
      {
        nfiles++;
        // log_debug("Detected file: %s", string - cur_line_len);
      }
      string++;
      // log_debug("String now:  %s", string);
      total_len++;
      cur_line_len = 0;
    }
  }
  free(tmp);
  return nfiles;
}

/**
 * @brief Counts the number of files in a WFP file. It reads the file as a stream into a buffer and returns the number of file entries.
 * @param filename The file name to be analized.
 * @return return the number of files in the string. Returns 0 if the buffer is empty or equal to 0. Return -1 and log the error if an error occurs.
 */

int wfp_count_files(char *filename)
{
  if (!is_file(filename))
  {
    log_error("WFP file does not exist: %s", filename);
    return -1;
  }
  // buffered read of the file
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    log_error("Error opening WFP file: %s", filename);
    return -1;
  }

  int read_size = 0;
  int nfiles = 0;
  do
  {
    char *buf = calloc(WFP_BUFFER_SIZE, 1);
    read_size = fread(buf, sizeof(char), WFP_BUFFER_SIZE - 1, fp);
    nfiles += wfp_count_files_in_string(buf);
    free(buf);

  } while (read_size == WFP_BUFFER_SIZE); // Loop while we read a full buffer

  fclose(fp);
  log_debug("WFP File: %s has %d files", filename, nfiles);
  return nfiles;
}