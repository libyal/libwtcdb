/*
 * Cache entry functions
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBWTCDB_CACHE_ENTRY_H )
#define _LIBWTCDB_CACHE_ENTRY_H

#include <common.h>
#include <types.h>

#include "libwtcdb_io_handle.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwtcdb_cache_entry libwtcdb_cache_entry_t;

struct libwtcdb_cache_entry
{
	/* The data size
	 */
	uint32_t data_size;

	/* The hash
	 */
	uint64_t hash;

	/* The identifier size
	 */
	uint32_t identifier_size;

	/* The padding size
	 */
	uint32_t padding_size;

	/* The cached data size
	 */
	uint32_t cached_data_size;

	/* The identifier
	 */
	uint8_t *identifier;

	/* The data CRC
	 */
	uint64_t data_crc;
};

int libwtcdb_cache_entry_initialize(
     libwtcdb_cache_entry_t **cache_entry,
     libcerror_error_t **error );

int libwtcdb_cache_entry_free(
     libwtcdb_cache_entry_t **cache_entry,
     libcerror_error_t **error );

int libwtcdb_cache_entry_header_read_data(
     libwtcdb_cache_entry_t *cache_entry,
     libwtcdb_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libwtcdb_cache_entry_read_file_io_handle(
     libwtcdb_cache_entry_t *cache_entry,
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWTCDB_CACHE_ENTRY_H ) */

