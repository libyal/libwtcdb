/*
 * Item functions
 *
 * Copyright (C) 2010-2023, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libwtcdb_definitions.h"
#include "libwtcdb_io_handle.h"
#include "libwtcdb_item.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libcerror.h"

/* Creates an item
 * Make sure the value item is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_item_initialize(
     libwtcdb_item_t **item,
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     intptr_t *entry,
     libcerror_error_t **error )
{
	libwtcdb_internal_item_t *internal_item = NULL;
	static char *function                   = "libwtcdb_item_initialize";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid item value already set.",
		 function );

		return( -1 );
	}
	if( entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	internal_item = memory_allocate_structure(
	                 libwtcdb_internal_item_t );

	if( internal_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_item,
	     0,
	     sizeof( libwtcdb_internal_item_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear item.",
		 function );

		memory_free(
		 internal_item );

		return( -1 );
	}
	internal_item->io_handle      = io_handle;
	internal_item->file_io_handle = file_io_handle;
	internal_item->entry          = entry;

	*item = (libwtcdb_item_t *) internal_item;

	return( 1 );

on_error:
	if( internal_item != NULL )
	{
		memory_free(
		 internal_item );
	}
	return( -1 );
}

/* Frees an item
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_item_free(
     libwtcdb_item_t **item,
     libcerror_error_t **error )
{
	libwtcdb_internal_item_t *internal_item = NULL;
	static char *function                   = "libwtcdb_item_free";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		internal_item = (libwtcdb_internal_item_t *) *item;
		*item         = NULL;

		/* The io_handle, file_io_handle and entry references are freed elsewhere
		 */
		memory_free(
		 internal_item );
	}
	return( 1 );
}

