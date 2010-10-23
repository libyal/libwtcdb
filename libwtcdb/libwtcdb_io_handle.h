/*
 * Input/Output (IO) handle
 *
 * Copyright (c) 2010, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <liberror.h>

#include "libwtcdb_array_type.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libfvalue.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t *wtcdb_database_file_signature;
extern const uint8_t *wtcdb_index_file_signature;

typedef struct libwtcdb_io_handle libwtcdb_io_handle_t;

struct libwtcdb_io_handle
{
	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libwtcdb_io_handle_initialize(
     libwtcdb_io_handle_t **io_handle,
     liberror_error_t **error );

int libwtcdb_io_handle_free(
     libwtcdb_io_handle_t **io_handle,
     liberror_error_t **error );

int libwtcdb_io_handle_read_file_header(
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *first_thumbnail_entry_offset,
     uint32_t *number_of_thumbnail_entries,
     liberror_error_t **error );

int libwtcdb_io_handle_read_items(
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t first_thumbnail_entry_offset,
     uint32_t number_of_items,
     libwtcdb_array_t *items_array,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

