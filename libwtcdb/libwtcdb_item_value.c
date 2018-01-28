/*
 * Item value functions
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libwtcdb_item_value.h"
#include "libwtcdb_libcerror.h"
#include "libwtcdb_types.h"

/* Creates an item value
 * Make sure the value item_value is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_item_value_initialize(
     libwtcdb_item_value_t **item_value,
     libcerror_error_t **error )
{
	static char *function = "libwtcdb_item_value_initialize";

	if( item_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item value.",
		 function );

		return( -1 );
	}
	if( *item_value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid item value value already set.",
		 function );

		return( -1 );
	}
	*item_value = memory_allocate_structure(
	               libwtcdb_item_value_t );

	if( *item_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create item value.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *item_value,
	     0,
	     sizeof( libwtcdb_item_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear item value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *item_value != NULL )
	{
		memory_free(
		 *item_value );

		*item_value = NULL;
	}
	return( -1 );
}

/* Frees an item value
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_item_value_free(
     libwtcdb_item_value_t **item_value,
     libcerror_error_t **error )
{
	static char *function = "libwtcdb_item_value_free";

	if( item_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item value.",
		 function );

		return( -1 );
	}
	if( *item_value != NULL )
	{
		if( ( *item_value )->identifier != NULL )
		{
			memory_free(
			 ( *item_value )->identifier );
		}
		memory_free(
		 *item_value );

		*item_value = NULL;
	}
	return( 1 );
}

