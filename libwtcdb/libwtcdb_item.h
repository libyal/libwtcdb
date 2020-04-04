/*
 * Item functions
 *
 * Copyright (C) 2010-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBWTCDB_INTERNAL_ITEM_H )
#define _LIBWTCDB_INTERNAL_ITEM_H

#include <common.h>
#include <types.h>

#include "libwtcdb_extern.h"
#include "libwtcdb_io_handle.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libcerror.h"
#include "libwtcdb_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwtcdb_internal_item libwtcdb_internal_item_t;

struct libwtcdb_internal_item
{
	/* The IO handle
	 */
	libwtcdb_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The entry
	 */
	intptr_t *entry;
};

int libwtcdb_item_initialize(
     libwtcdb_item_t **item,
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     intptr_t *entry,
     libcerror_error_t **error );

LIBWTCDB_EXTERN \
int libwtcdb_item_free(
     libwtcdb_item_t **item,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWTCDB_INTERNAL_ITEM_H ) */

