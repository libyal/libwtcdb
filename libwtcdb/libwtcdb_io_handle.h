/*
 * Input/Output (IO) handle
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBWTCDB_IO_HANDLE_H )
#define _LIBWTCDB_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libwtcdb_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t *wtcdb_cache_file_signature;
extern const uint8_t *wtcdb_index_file_signature;

typedef struct libwtcdb_io_handle libwtcdb_io_handle_t;

struct libwtcdb_io_handle
{
	/* The file type
	 */
	uint8_t file_type;

	/* The format version
	 */
	uint32_t format_version;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libwtcdb_io_handle_initialize(
     libwtcdb_io_handle_t **io_handle,
     libcerror_error_t **error );

int libwtcdb_io_handle_free(
     libwtcdb_io_handle_t **io_handle,
     libcerror_error_t **error );

int libwtcdb_io_handle_clear(
     libwtcdb_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWTCDB_IO_HANDLE_H ) */

