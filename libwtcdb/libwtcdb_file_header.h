/*
 * File header functions
 *
 * Copyright (C) 2010-2021, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBWTCDB_FILE_HEADER_H )
#define _LIBWTCDB_FILE_HEADER_H

#include <common.h>
#include <types.h>

#include "libwtcdb_libbfio.h"
#include "libwtcdb_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwtcdb_file_header libwtcdb_file_header_t;

struct libwtcdb_file_header
{
	/* The file type
	 */
	uint8_t file_type;

	/* The format version
	 */
	uint32_t format_version;

	/* The cache type
	 */
	uint32_t cache_type;

	/* The first entry offset
	 */
	uint32_t first_entry_offset;

	/* The available cache entry offset
	 */
	uint32_t available_cache_entry_offset;

	/* The number of entries
	 */
	uint32_t number_of_entries;
};

int libwtcdb_file_header_initialize(
     libwtcdb_file_header_t **file_header,
     libcerror_error_t **error );

int libwtcdb_file_header_free(
     libwtcdb_file_header_t **file_header,
     libcerror_error_t **error );

int libwtcdb_file_header_read_data(
     libwtcdb_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libwtcdb_file_header_read_file_io_handle(
     libwtcdb_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWTCDB_FILE_HEADER_H ) */

