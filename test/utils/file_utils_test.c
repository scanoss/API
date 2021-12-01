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
  * @file file_utils_test.c
  * @date 12 July 2020 
  * @brief Contains functions to test the file_utils.c functions.The results of each test are shown in the console.
  */



#include <sys/stat.h>
#include "snow.h"
#include "../../src/utils/file_utils.h"

describe(file_utils)
{
  subdesc(list_files_in_dir)
  {
    it("should list all files in a directory")
    {
      files_list list = list_files_in_dir("test");

      assert(list.n_files > 0);
      for (int i = 0; i < list.n_files; i++)
      {
        free(list.files[i]);
      }
    }

    it("should return empty if no files in directory")
    {
      char *tmpdir = "/tmp/file_utils_test";
      mkdir(tmpdir, 0755);
      files_list list = list_files_in_dir(tmpdir);
      assert(list.n_files == 0);
      rmdir(tmpdir);
    }
  }

  subdesc(is_zip_file)
  {
    it("detects zip file case independent")
    {
      assert(is_zip_file("/test/file.Zip"));
    }

    it("detects zip file in path with extra dots")
    {
      assert(is_zip_file("/this/is.a.path/with.dots.zip"));
    }
  }

  subdesc(is_wfp_file)
  {
    it("detects wfp file")
    {
      assert(is_wfp_file("/test/file.wfp"));
    }
  }
}