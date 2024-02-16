/*
 * Notification functions
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

#if !defined( _LIBWTCDB_NOTIFY_H )
#define _LIBWTCDB_NOTIFY_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "libwtcdb_extern.h"
#include "libwtcdb_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBWTCDB )

LIBWTCDB_EXTERN \
void libwtcdb_notify_set_verbose(
      int verbose );

LIBWTCDB_EXTERN \
int libwtcdb_notify_set_stream(
     FILE *stream,
     libcerror_error_t **error );

LIBWTCDB_EXTERN \
int libwtcdb_notify_stream_open(
     const char *filename,
     libcerror_error_t **error );

LIBWTCDB_EXTERN \
int libwtcdb_notify_stream_close(
     libcerror_error_t **error );

#endif /* !defined( HAVE_LOCAL_LIBWTCDB ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWTCDB_NOTIFY_H ) */

