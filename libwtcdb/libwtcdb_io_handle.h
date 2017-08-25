/*
 * Input/Output (IO) handle
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBWTCDB_IO_HANDLE_H )
#define _LIBWTCDB_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libwtcdb_item_value.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libcdata.h"
#include "libwtcdb_libcerror.h"
#include "libwtcdb_libfvalue.h"

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

	/* The version
	 */
	uint32_t version;

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

int libwtcdb_io_handle_read_file_header(
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *first_entry_offset,
     uint32_t *available_cache_entry_offset,
     uint32_t *number_of_entries,
     libcerror_error_t **error );

int libwtcdb_io_handle_read_items(
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t first_entry_offset,
     uint32_t available_cache_entry_offset,
     uint32_t number_of_items,
     libcdata_array_t *items_array,
     libcerror_error_t **error );

int libwtcdb_io_handle_read_cache_entry_data(
     libwtcdb_io_handle_t *io_handle,
     libwtcdb_item_value_t *item_value,
     uint32_t item_iterator,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWTCDB_IO_HANDLE_H ) */

