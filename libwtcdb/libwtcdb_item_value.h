/*
 * Item value functions
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

#if !defined( _LIBWTCDB_ITEM_VALUE_H )
#define _LIBWTCDB_ITEM_VALUE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libwtcdb_extern.h"
#include "libwtcdb_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwtcdb_item_value libwtcdb_item_value_t;

struct libwtcdb_item_value
{
	/* The identifier
	 */
	uint8_t *identifier;

	/* The identifier size
	 */
	size_t identifier_size;
};

int libwtcdb_item_value_initialize(
     libwtcdb_item_value_t **item_value,
     liberror_error_t **error );

int libwtcdb_item_value_free(
     intptr_t *item_value,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

