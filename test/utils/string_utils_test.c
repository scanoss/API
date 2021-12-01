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
  * @file string_utils_test.c
  * @date 12 July 2020 
  * @brief Contains functions to test the string_utils.c functions. The results of each test are shown in the console.
  */


#include "snow.h"
#include "../../src/utils/string_utils.h"

describe(string_utils)
{
  subdesc(string_fast_strcat)
  {
    it("Concatenates string")
    {
      char one[64];

      sprintf(one, "One");
      char *tmp = one;
      char *two = "Two";
      string_fast_strcat(tmp, two);
      asserteq(one, "OneTwo");
    }
  }
  subdesc(extract_ulong)
  {
    it("extracts a long")
    {
      asserteq(extract_ulong("testl", "testl=1234"), 1234);
    }

    it("returns zero if value is not a number")
    {
      char *input = "testl=notanumber";
      asserteq(extract_ulong("testl", input), 0);
    }
  }

  subdesc(extract_qs_value)
  {
    it("Returns NULL if input string is empty")
    {
      assert(extract_qs_value("", "key", 100) == NULL);
    }

    it("Returns value from beginning of query string")
    {
      char *qs = "key1=value1&key2=value2";
      char *value = extract_qs_value(qs, "key1", 10);
      asserteq(value, "value1");
      free(value);
    }

    it("Returns value from middle of query string")
    {
      char *qs = "key1=value1&key2=value2&key3=value3";
      char *value = extract_qs_value(qs, "key2", 10);
      asserteq(value, "value2");
      free(value);
    }

    it("Returns value from end of query string")
    {
      char *qs = "key1=value1&key2=value2";
      char *value = extract_qs_value(qs, "key2", 10);
      asserteq(value, "value2");
      free(value);
    }

    it("Trims string if length exceeds maximum length")
    {
      char *qs = "key1=value1&key2=value2";
      char *value = extract_qs_value(qs, "key2", 4);
      asserteq(value, "val");
      free(value);
    }

    it("Returns NULL if value is not found")
    {
      assert(extract_qs_value("key1=value1&key2=value2", "nonkey", 20) == NULL);
    }
  }
}