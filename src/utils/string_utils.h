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
#ifndef __SCANOSS_BASE_STRING_UTILS_H
#define __SCANOSS_BASE_STRING_UTILS_H

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of strings that can be handled by split method.
#define MAX_SPLIT_STR 50


// Maximum length of a string representing an integer number.
#define MAX_INT_STR 32

// Useful macro to free a string array of known size.
#define free_string_array(size, array) \
  {                                    \
    for (int i = 0; i < size; i++)     \
    {                                  \
      free(array[i]);                  \
    }                                  \
    free(array);                       \
  }

/**
 * string_fast_strcat: Fast implementation of strcat
 */
char *string_fast_strcat(char *dest, char *src);


bool valid_alpha(char *data);

bool string_isdigit(char *data);

/**
 * extract_qs_value: Extracts a value from an input query string, corresponding to the key specified. 
 * The output string is guaranteed to have a maximun size of max_len.
 * 
 * If the query string does not contain the key specified, the function returns NULL.
 * 
 */
char *extract_qs_value(char *in, char *key, long max_len);

/**
 * extract_ulong: Extracts an unsigned long from the input string in the key given. 
 */
uint64_t extract_ulong(char *key, char *in);

/**
 * extract_uint32_t: Extracts an unsigned int from the input string in the key given.
 */
uint32_t extract_uint32_t(char *key, char *in);

void hexprint(uint8_t *data, uint32_t len);

/**
 * startswith: Returns true if str starts with prefix. 
 */
bool startswith(char *str, const char *prefix);

/**
 * startswithany: Checks if any of the strings in the list is contained in the string str and returns true 
 * otherwise it returns false.  
 * 
 * IMPORTANT: list has to be an array of strings with the last element an empty string, "". This saves having to add 
 * an extra argument with the size of the array. 
 */
bool startswithany(char *str, const char *list[]);
#endif