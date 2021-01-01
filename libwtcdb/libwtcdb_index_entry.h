/*
 * Cache entry functions
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

#if !defined( _LIBWTCDB_INDEX_ENTRY_H )
#define _LIBWTCDB_INDEX_ENTRY_H

#include <common.h>
#include <types.h>

#include "libwtcdb_io_handle.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwtcdb_index_entry libwtcdb_index_entry_t;

struct libwtcdb_index_entry
{
	/* The data size
	 */
	uint32_t data_size;

	/* The hash
	 */
	uint64_t hash;

	/* The modification date and time
	 */
	uint64_t modification_time;
};

int libwtcdb_index_entry_initialize(
     libwtcdb_index_entry_t **index_entry,
     libcerror_error_t **error );

int libwtcdb_index_entry_free(
     libwtcdb_index_entry_t **index_entry,
     libcerror_error_t **error );

int libwtcdb_index_entry_read_data(
     libwtcdb_index_entry_t *index_entry,
     libwtcdb_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libwtcdb_index_entry_read_file_io_handle(
     libwtcdb_index_entry_t *index_entry,
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWTCDB_INDEX_ENTRY_H ) */

