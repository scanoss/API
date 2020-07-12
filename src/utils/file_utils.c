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
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/md5.h>

#include "file_utils.h"
/*
 * list_files_in_dir: List all files in a directory
 */
files_list list_files_in_dir(char *dirname)
{

  struct dirent *entry;
  files_list list;

  // opendir() returns a pointer of DIR type.
  DIR *dr = opendir(dirname);

  if (dr == NULL)
  {

    return list;
  }

  int n_files = 0;
  while ((entry = readdir(dr)) != NULL)
  {
    // ignore pointers to current and parent folders
    if (strcmp("..", entry->d_name) && strcmp(".", entry->d_name) && strstr(entry->d_name, "-journal") == NULL)
    {
      list.files[n_files] = strdup(entry->d_name);
      n_files++;
    }
  }
  list.n_files = n_files;

  closedir(dr);
  return list;
}

void free_files_list(files_list list)
{
  for (int i = 0; i < list.n_files; i++)
  {
    free(list.files[i]);
  }
}

bool file_exists(char *fname)
{
  return access(fname, F_OK) != -1;
}

uint64_t file_size(char *path)
{
  uint64_t length = 0;
  FILE *file = fopen(path, "rb");
  if (file)
  {
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fclose(file);
  }
  return length;
}

char *file_extension(char *path)
{
  if (strlen(path) == 0)
  {
    return NULL;
  }

  char *dot = strrchr(path, '.');
  char *slash = strrchr(path, '/');

  if (!dot && !slash)
    return NULL;
  if (dot > slash)
    return dot + 1;
  if (slash != path)
    return slash + 1;
  return NULL;
}

bool file_has_ext(char *path, char *ext)
{
  char extension[20];

  if (file_extension(path))
  {
    strcpy(extension, file_extension(path));
  }

  return strcasecmp(extension, ext) == 0;
}

bool is_wfp_file(char *path)
{
  return file_has_ext(path, "wfp");
}

bool is_zip_file(char *path)
{
  return file_has_ext(path, "zip");
}

uint8_t *file_md5(char *filepath)
{

  uint8_t *c = calloc(16, 1);
  FILE *inFile = fopen(filepath, "rb");
  MD5_CTX mdContext;
  int bytes;
  unsigned char data[1024];

  if (inFile != NULL)
  {
    MD5_Init(&mdContext);
    while ((bytes = fread(data, 1, 1024, inFile)) != 0)
    {
      MD5_Update(&mdContext, data, bytes);
    }
    MD5_Final(c, &mdContext);
    fclose(inFile);
  }
  return c;
}