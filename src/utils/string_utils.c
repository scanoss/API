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
  * @file string_utils.c
  * @date 12 July 2020 
  * @brief Contains functions to extract data from JSON.
  */

#include <stdio.h>
#include "string_utils.h"

/**
 * @brief concatate two strings. 
 * @param src string to concat
 * @param dest string that will be concat to src. It needs to be big enough to accommodate the concatenation.
 * @return return the concatenation of the strings
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

/**
 * @brief know if a string has a digit
 * @param data string to be analized
 * @return return true if a contains a digit and false otherwise
 */

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
 * @brief extracts a value from an input query string, corresponding to the key specified.
 * The output string is guaranteed to have a maximun size of max_len.
 * @param in request form
 * @param key key to be extracted
 * @param max_len length of the output string
 * @return return the value of the key. NULL if the key is not found.
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
 * @brief Extracts an unsigned long from the input string in the key given.
 * @param key key to be extracted
 * @param in request form
 * @return return the value of the key. 0 if the key is not found or the value is not a number.
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
 * @brief Extracts an unsigned int from the input string in the key given.
 * @param key key to be extracted
 * @param in request form
 * @return return the value of the key. 0 if the key is not found or the value is not a number.
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



  /**
 * @brief Print data in hexadecimal format
 * @param data Data to be printed in hexadecimal format
 * @param len Length of the data
 
 */

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
