/*
 * libwtcdb file
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
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include "libwtcdb_cache_entry.h"
#include "libwtcdb_debug.h"
#include "libwtcdb_definitions.h"
#include "libwtcdb_index_entry.h"
#include "libwtcdb_io_handle.h"
#include "libwtcdb_item.h"
#include "libwtcdb_file.h"
#include "libwtcdb_file_header.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libcdata.h"
#include "libwtcdb_libcerror.h"
#include "libwtcdb_libcnotify.h"

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_initialize(
     libwtcdb_file_t **file,
     libcerror_error_t **error )
{
	libwtcdb_internal_file_t *internal_file = NULL;
	static char *function                   = "libwtcdb_file_initialize";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( *file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file value already set.",
		 function );

		return( -1 );
	}
	internal_file = memory_allocate_structure(
	                 libwtcdb_internal_file_t );

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_file,
	     0,
	     sizeof( libwtcdb_internal_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		memory_free(
		 internal_file );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_file->entries ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entries array.",
		 function );

		goto on_error;
	}
	if( libwtcdb_io_handle_initialize(
	     &( internal_file->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	*file = (libwtcdb_file_t *) internal_file;

	return( 1 );

on_error:
	if( internal_file != NULL )
	{
		if( internal_file->entries != NULL )
		{
			libcdata_array_free(
			 &( internal_file->entries ),
			 NULL,
			 NULL );
		}
		memory_free(
		 internal_file );
	}
	return( -1 );
}

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_free(
     libwtcdb_file_t **file,
     libcerror_error_t **error )
{
	libwtcdb_internal_file_t *internal_file = NULL;
	static char *function                   = "libwtcdb_file_free";
	int result                              = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( *file != NULL )
	{
		internal_file = (libwtcdb_internal_file_t *) *file;

		if( internal_file->file_io_handle != NULL )
		{
			if( libwtcdb_file_close(
			     *file,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close file.",
				 function );

				result = -1;
			}
		}
		*file = NULL;

		if( libcdata_array_free(
		     &( internal_file->entries ),
		     (int (*)(intptr_t **, libcerror_error_t **)) internal_file->entry_free_function,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free entries array.",
			 function );

			result = -1;
		}
		if( libwtcdb_io_handle_free(
		     &( internal_file->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_file );
	}
	return( result );
}

/* Signals the file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_signal_abort(
     libwtcdb_file_t *file,
     libcerror_error_t **error )
{
	libwtcdb_internal_file_t *internal_file = NULL;
	static char *function                   = "libwtcdb_file_signal_abort";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libwtcdb_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_file->io_handle->abort = 1;

	return( 1 );
}

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_open(
     libwtcdb_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle        = NULL;
	libwtcdb_internal_file_t *internal_file = NULL;
	static char *function                   = "libwtcdb_file_open";
	size_t filename_length                  = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libwtcdb_internal_file_t *) file;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBWTCDB_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBWTCDB_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBWTCDB_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libwtcdb_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %s.",
		 function,
		 filename );

		goto on_error;
	}
	internal_file->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_open_wide(
     libwtcdb_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle        = NULL;
	libwtcdb_internal_file_t *internal_file = NULL;
	static char *function                   = "libwtcdb_file_open_wide";
	size_t filename_length                  = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libwtcdb_internal_file_t *) file;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBWTCDB_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBWTCDB_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBWTCDB_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libwtcdb_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	internal_file->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_open_file_io_handle(
     libwtcdb_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libwtcdb_internal_file_t *internal_file = NULL;
	static char *function                   = "libwtcdb_file_open_file_io_handle";
	int bfio_access_flags                   = 0;
	int file_io_handle_is_open              = 0;
	int file_io_handle_opened_in_library    = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libwtcdb_internal_file_t *) file;

	if( internal_file->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - file IO handle already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBWTCDB_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBWTCDB_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBWTCDB_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBWTCDB_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to determine if file IO handle is open.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( libwtcdb_file_open_read(
	     internal_file,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file handle.",
		 function );

		goto on_error;
	}
	internal_file->file_io_handle                   = file_io_handle;
	internal_file->file_io_handle_opened_in_library = file_io_handle_opened_in_library;

	return( 1 );

on_error:
	if( file_io_handle_opened_in_library != 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
int libwtcdb_file_close(
     libwtcdb_file_t *file,
     libcerror_error_t **error )
{
	libwtcdb_internal_file_t *internal_file = NULL;
	static char *function                   = "libwtcdb_file_close";
	int result                              = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libwtcdb_internal_file_t *) file;

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_file->file_io_handle_created_in_library != 0 )
		{
			if( libwtcdb_debug_print_read_offsets(
			     internal_file->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_file->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_file->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_opened_in_library = 0;
	}
	if( internal_file->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_file->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_created_in_library = 0;
	}
	internal_file->file_io_handle = NULL;

	if( libwtcdb_io_handle_clear(
	     internal_file->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_file->entries,
	     (int (*)(intptr_t **, libcerror_error_t **)) internal_file->entry_free_function,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty entries array.",
		 function );

		result = -1;
	}
	return( result );
}

/* Opens a file for reading
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_open_read(
     libwtcdb_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libwtcdb_file_header_t *file_header = NULL;
	static char *function               = "libwtcdb_file_open_read";
	int result                          = 1;

#if defined( HAVE_DEBUG_OUTPUT )
	uint8_t *trailing_data              = NULL;
	size_t trailing_data_size           = 0;
	ssize_t read_count                  = 0;
#endif

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle->abort != 0 )
	{
		internal_file->io_handle->abort = 0;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading file header:\n" );
	}
#endif
	if( libwtcdb_file_header_initialize(
	     &file_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file header.",
		 function );

		goto on_error;
	}
	if( libwtcdb_file_header_read_file_io_handle(
	     file_header,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		goto on_error;
	}
	internal_file->io_handle->file_type      = file_header->file_type;
	internal_file->io_handle->format_version = file_header->format_version;

	if( internal_file->io_handle->file_type == LIBWTCDB_FILE_TYPE_CACHE )
	{
		internal_file->entry_free_function = (intptr_t *) &libwtcdb_cache_entry_free;
	}
	else if( internal_file->io_handle->file_type == LIBWTCDB_FILE_TYPE_INDEX )
	{
		internal_file->entry_free_function = (intptr_t *) &libwtcdb_index_entry_free;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( file_header->first_entry_offset > 24 )
		{
			trailing_data_size = (size_t) ( file_header->first_entry_offset - 24 );

			trailing_data = (uint8_t *) memory_allocate(
			                             sizeof( uint8_t ) * trailing_data_size );

			if( trailing_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create trailing data.",
				 function );

				goto on_error;
			}
			read_count = libbfio_handle_read_buffer(
				      file_io_handle,
				      trailing_data,
				      trailing_data_size,
				      error );

			if( read_count != (ssize_t) trailing_data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read trailing data.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 trailing_data,
			 trailing_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

			memory_free(
			 trailing_data );

			trailing_data = NULL;
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading entries:\n" );
	}
#endif
	result = libwtcdb_file_read_entries(
	          internal_file,
	          file_io_handle,
	          file_header->first_entry_offset,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read entries.",
		 function );
	}
	if( libwtcdb_file_header_free(
	     &file_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file header.",
		 function );

		goto on_error;
	}
	if( internal_file->io_handle->abort != 0 )
	{
		internal_file->io_handle->abort = 0;
	}
	return( result );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( trailing_data != NULL )
	{
		memory_free(
		 trailing_data );
	}
#endif
	if( file_header != NULL )
	{
		libwtcdb_file_header_free(
		 &file_header,
		 NULL );
	}
	return( -1 );
}

/* Reads the entries into the entries array
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_read_entries(
     libwtcdb_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     uint32_t first_entry_offset,
     libcerror_error_t **error )
{
	libwtcdb_cache_entry_t *cache_entry = NULL;
	libwtcdb_index_entry_t *index_entry = NULL;
	static char *function               = "libwtcdb_file_read_entries";
	off64_t file_offset                 = 0;
	size64_t file_size                  = 0;
	int entry_index                     = 0;
	int entry_iterator                  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	const char *type_string             = NULL;
#endif

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( internal_file->io_handle->file_type != LIBWTCDB_FILE_TYPE_CACHE )
	 && ( internal_file->io_handle->file_type != LIBWTCDB_FILE_TYPE_INDEX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file type.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( internal_file->io_handle->file_type == LIBWTCDB_FILE_TYPE_CACHE )
	{
		type_string = "cache";
	}
	else if( internal_file->io_handle->file_type == LIBWTCDB_FILE_TYPE_INDEX )
	{
		type_string = "index";
	}
#endif
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		goto on_error;
	}
	file_offset = (off64_t) first_entry_offset;

	while( (size64_t) file_offset < file_size )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading %s entry: %d at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
			 function,
			 type_string,
			 entry_iterator,
			 file_offset,
			 file_offset );
		}
#endif
		if( internal_file->io_handle->file_type == LIBWTCDB_FILE_TYPE_CACHE )
		{
			if( libwtcdb_cache_entry_initialize(
			     &cache_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create cache entry.",
				 function );

				goto on_error;
			}
			if( libwtcdb_cache_entry_read_file_io_handle(
			     cache_entry,
			     internal_file->io_handle,
			     file_io_handle,
			     file_offset,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read cache entry: %d.",
				 function,
				 entry_iterator );

				goto on_error;
			}
			file_offset += (size_t) cache_entry->data_size;

			if( cache_entry->hash == 0 )
			{
				if( libwtcdb_cache_entry_free(
				     &cache_entry,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free cache entry.",
					 function );

					goto on_error;
				}
			}
			else
			{
				if( libcdata_array_append_entry(
				     internal_file->entries,
				     &entry_index,
				     (intptr_t *) cache_entry,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append cache entry to array.",
					 function );

					goto on_error;
				}
				cache_entry = NULL;
			}
		}
		else if( internal_file->io_handle->file_type == LIBWTCDB_FILE_TYPE_INDEX )
		{
			if( libwtcdb_index_entry_initialize(
			     &index_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create index entry.",
				 function );

				goto on_error;
			}
			if( libwtcdb_index_entry_read_file_io_handle(
			     index_entry,
			     internal_file->io_handle,
			     file_io_handle,
			     file_offset,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read index entry: %d.",
				 function,
				 entry_iterator );

				goto on_error;
			}
			file_offset += (size_t) index_entry->data_size;

			if( index_entry->hash == 0 )
			{
				if( libwtcdb_index_entry_free(
				     &index_entry,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free index entry.",
					 function );

					goto on_error;
				}
			}
			else
			{
				if( libcdata_array_append_entry(
				     internal_file->entries,
				     &entry_index,
				     (intptr_t *) index_entry,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append index entry to array.",
					 function );

					goto on_error;
				}
				index_entry = NULL;
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
		entry_iterator++;
	}
	return( 1 );

on_error:
	if( index_entry != NULL )
	{
		libwtcdb_index_entry_free(
		 &index_entry,
		 NULL );
	}
	if( cache_entry != NULL )
	{
		libwtcdb_cache_entry_free(
		 &cache_entry,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the file type
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_get_type(
     libwtcdb_file_t *file,
     uint8_t *type,
     libcerror_error_t **error )
{
	libwtcdb_internal_file_t *internal_file = NULL;
	static char *function                   = "libwtcdb_file_get_type";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libwtcdb_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = internal_file->io_handle->file_type;

	return( 1 );
}

/* Retrieves the number of items
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_get_number_of_items(
     libwtcdb_file_t *file,
     int *number_of_items,
     libcerror_error_t **error )
{
	libwtcdb_internal_file_t *internal_file = NULL;
	static char *function                   = "libwtcdb_file_get_number_of_items";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libwtcdb_internal_file_t *) file;

	if( libcdata_array_get_number_of_entries(
	     internal_file->entries,
	     number_of_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific item
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_get_item(
     libwtcdb_file_t *file,
     int item_index,
     libwtcdb_item_t **item,
     libcerror_error_t **error )
{
	libwtcdb_internal_file_t *internal_file = NULL;
 	intptr_t *entry                         = NULL;
	static char *function                   = "libwtcdb_file_get_item";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libwtcdb_internal_file_t *) file;

	if( internal_file->entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing entries array.",
		 function );

		return( -1 );
	}
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
	if( libcdata_array_get_entry_by_index(
	     internal_file->entries,
	     item_index,
	     &entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 item_index );

		return( -1 );
	}
	if( libwtcdb_item_initialize(
	     item,
	     internal_file->io_handle,
	     internal_file->file_io_handle,
	     entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item.",
		 function );

		return( -1 );
	}
	return( 1 );
}

