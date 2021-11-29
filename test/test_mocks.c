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
 * This file mocks system functions used in the code. 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/ssl.h>

#define BUFFER_SIZE 16384

char *buf;
int remaining_bytes;
int buf_size;



/**
 * @brief Initialises mock socket buffer. Should be balled with every test.
 */
void init_mock_socket_buffer()
{
  buf = calloc(BUFFER_SIZE, sizeof(char));
  remaining_bytes = BUFFER_SIZE - 1;
  buf_size = BUFFER_SIZE;
}

/**
 * Mock socket send function.
 */
int send(int socket, const void *out, int size, int offset)
{
  if (buf == NULL)
  {
    init_mock_socket_buffer();
  }

  if (remaining_bytes < size)
  {
    // Increase buffer size
    buf = realloc(buf, buf_size + size);
    buf_size += size;
    remaining_bytes += size;
  }
  if (out != NULL && strcmp("", (char *)out))
  {
    strcat(buf, out);
    remaining_bytes -= size;
  }
  return 0;
}

int SSL_write(SSL *ssl, const void *buf, int size)
{
  return send(0, buf, size, 0);
}

char *get_sent_data()
{
  char *data_sent = strdup(buf);
  free(buf);
  return data_sent;
}

