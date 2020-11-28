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
 * file_utils.h
 * 
 * Generic file utilities.
 */
#ifndef __SCANOSS_BASE_FILE_UTILS_H
#define __SCANOSS_BASE_FILE_UTILS_H

#include <stdbool.h>
#include <stdint.h>

// Maximum files in a folder
#define MAX_FILES_IN_FOLDER 1024

typedef struct files_list
{
  int n_files;
  char *files[MAX_FILES_IN_FOLDER];
} files_list;

files_list list_files_in_dir(char *dirname);
void free_files_list(files_list list);
bool file_exists(char *fname);

/**
 * file_extension: Returns the file extension of the file or empty if the file has no extension. 
 */
char *file_extension(char *path);

/**
 * file_size: Returns the size of the file in bytes. 
 */
uint64_t file_size(char *path);
bool find_in_file(char *path, char *needle);
bool is_dir(char *path);
bool is_file(char *path);
bool is_zip_file(char *path);
bool is_wfp_file(char *path);
void read_file(char *out, char *path, uint64_t maxlen);
void write_file(char *filename, char *ptr, int size);

uint8_t *file_md5(char *filepath);

#endif