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
#include <stdio.h>
#include "string_utils.h"

/**
 * string_fast_strcat: Very fast string concatenation. Pass a copy of the original destination string as the 'dest' argument. 
 * This is because the algorithm returns the original pointer displaced. The destination pointer needs to be big enough to accommodate the concatenation.
 * This is done for speed. Check test in test/string_utils_test.c
 */
char *string_fast_strcat(char *dest, char *src)
{
  while (*dest)
    dest++;
  while ((*dest++ = *src++))
    ;
  return --dest;
} 


bool valid_alpha(char *data)
{

  if (data[0] == 0)
    return false;

  for (int i = 0; i < strlen(data); i++)
    if (!isalnum(data[i]) && data[i] != 95 && data[i] != 45)
      return false;

  return true;
}

bool string_isdigit(char *data)
{

  if (data == NULL || data[0] == 0)
    return false;

  for (int i = 0; i < strlen(data); i++)
    if (!isdigit(data[i]))
      return false;

  return true;
}

/**
 * extract_qs_value: Extracts a value from an input query string, corresponding to the key specified.
 * The output string is guaranteed to have a maximun size of max_len.
 *
 * If the query string does not contain the key specified, the function returns NULL.
 *
 * This is a safer form of extract_tag, designed to replace it.
 */
char *extract_qs_value(char *in, char *key, long max_len)
{
  if (!in || in[0] == 0 || strlen(in) == 0)
  {

    return NULL;
  }
  char *tag_str = calloc(strlen(key) + 2, sizeof(char));
  sprintf(tag_str, "%s=", key);

  // Pointer to the first character of the key
  char *key_ptr = strstr(in, tag_str);

  if (key_ptr == NULL)
  {
    free(tag_str);

    return NULL;
  }

  char *start = key_ptr + strlen(tag_str);
  char *end = strchr(start, '&');
  free(tag_str);
  // if value is at end of string just add NULL char at end of string and return.
  char *target;
  int target_size = 0;
  if (end != NULL)
  {
    target_size = end - start;
  }
  else
  {
    target_size = strlen(start);
  }
  target = malloc(target_size + 1);
  memcpy(target, start, target_size);
  target[target_size] = '\0';
  // Truncate the string if it's longer than max_len
  if (strlen(target) > max_len)
  {
    char *new_target = strndup(target, max_len - 1);
    free(target);
    return new_target;
  }
  return target;
}

/**
 * extract_ulong: Extracts an unsigned long from the input string in the key given.
 */
uint64_t extract_ulong(char *key, char *in)
{
  char *ulong_str = extract_qs_value(in, key, MAX_INT_STR);
  if (!string_isdigit(ulong_str))
  {
    free(ulong_str);
    return 0;
  }
  uint64_t result = strtol(ulong_str, NULL, 10);
  free(ulong_str);
  return result;
}

/**
 * extract_uint32_t: Extracts an unsigned int from the input string in the key given.
 */
uint32_t extract_uint32_t(char *key, char *in)
{
  char *ulong_str = extract_qs_value(in, key, MAX_INT_STR);
  if (!string_isdigit(ulong_str))
  {
    return 0;
  }
  uint32_t result = (uint32_t)strtol(ulong_str, NULL, 10);
  free(ulong_str);
  return result;
}

void hexprint(uint8_t *data, uint32_t len)
{
  uint8_t width = 16;
  uint8_t b16[] = "0123456789abcdef";
  for (int i = 0; i <= width * (int)((len + width) / width); i++)
    if (i && !(i % width))
    {
      printf("%04d  ", i - width);
      for (int t = i - width; t < i; t++)
        printf("%c%c ", t < len ? b16[(data[t] & 0xF0) >> 4] : 32, t < len ? b16[data[t] & 0x0F] : 32);
      printf(" ");
      for (int t = i - width; t < i; t++)
        printf("%c", t < len ? ((data[t] > 31 && data[t] < 127) ? data[t] : 46) : 32);
      printf("\n");
      if (i == len)
        break;
    }
}
