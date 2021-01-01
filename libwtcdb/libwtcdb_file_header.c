/*
 * File header functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libwtcdb_debug.h"
#include "libwtcdb_definitions.h"
#include "libwtcdb_file_header.h"
#include "libwtcdb_io_handle.h"
#include "libwtcdb_libcerror.h"
#include "libwtcdb_libcnotify.h"

#include "wtcdb_file_header.h"

/* Creates file header
 * Make sure the value file_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_header_initialize(
     libwtcdb_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libwtcdb_file_header_initialize";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file header value already set.",
		 function );

		return( -1 );
	}
	*file_header = memory_allocate_structure(
	                libwtcdb_file_header_t );

	if( *file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_header,
	     0,
	     sizeof( libwtcdb_file_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( -1 );
}

/* Frees file header
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_header_free(
     libwtcdb_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libwtcdb_file_header_free";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( 1 );
}

/* Reads the file header data
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_header_read_data(
     libwtcdb_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libwtcdb_file_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size < 24 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header:\n",
		 function );
		libcnotify_print_data(
		 data,
		 24,
		 0 );
	}
#endif
	if( memory_compare(
	     data,
	     wtcdb_cache_file_signature,
	     4 ) == 0 )
	{
		file_header->file_type = LIBWTCDB_FILE_TYPE_CACHE;
	}
	else if( memory_compare(
	          data,
	          wtcdb_index_file_signature,
	          4 ) == 0 )
	{
		file_header->file_type = LIBWTCDB_FILE_TYPE_INDEX;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ 4 ] ),
	 file_header->format_version );

	if( file_header->file_type == LIBWTCDB_FILE_TYPE_CACHE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_file_header_t *) data )->cache_type,
		 file_header->cache_type );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_file_header_t *) data )->first_cache_entry_offset,
		 file_header->first_entry_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_file_header_t *) data )->available_cache_entry_offset,
		 file_header->available_cache_entry_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_file_header_t *) data )->number_of_cache_entries,
		 file_header->number_of_entries );
	}
	else if( file_header->file_type == LIBWTCDB_FILE_TYPE_INDEX )
	{
		file_header->first_entry_offset = sizeof( wtcdb_index_file_header_t );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_index_file_header_t *) data )->number_of_index_entries,
		 file_header->number_of_entries );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 data[ 0 ],
		 data[ 1 ],
		 data[ 2 ],
		 data[ 3 ] );

		libcnotify_printf(
		 "%s: format version\t\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->format_version );

		if( file_header->file_type == LIBWTCDB_FILE_TYPE_CACHE )
		{
			libcnotify_printf(
			 "%s: cache type\t\t\t\t: %" PRIu32 "\n",
			 function,
			 file_header->cache_type );

			libcnotify_printf(
			 "%s: first cache entry offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 file_header->first_entry_offset );

			libcnotify_printf(
			 "%s: available cache entry offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 file_header->available_cache_entry_offset );

			libcnotify_printf(
			 "%s: number of cache entries\t\t\t: %" PRIu32 "\n",
			 function,
			 file_header->number_of_entries );
		}
		else if( file_header->file_type == LIBWTCDB_FILE_TYPE_INDEX )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_file_header_t *) data )->unknown1,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_file_header_t *) data )->number_of_index_entries_used,
			 value_32bit );
			libcnotify_printf(
			 "%s: number of index entries used\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: number of index entries\t\t\t: %" PRIu32 "\n",
			 function,
			 file_header->number_of_entries );

			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_file_header_t *) data )->unknown2,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif
	if( ( file_header->format_version != 20 )
	 && ( file_header->format_version != 21 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version: %" PRIu32 ".",
		 function,
		 file_header->format_version );

		return( -1 );
	}
	if( file_header->file_type == LIBWTCDB_FILE_TYPE_CACHE )
	{
		if( file_header->cache_type >= 5 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported cache type: %" PRIu32 ".",
			 function,
			 file_header->cache_type );

			return( -1 );
		}
		if( file_header->first_entry_offset < 24 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported first entry offset: %" PRIu32 ".",
			 function,
			 file_header->first_entry_offset );

			return( -1 );
		}
	}
	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_file_header_read_file_io_handle(
     libwtcdb_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t file_header_data[ 24 ];

	static char *function = "libwtcdb_file_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              file_header_data,
	              24,
	              0,
	              error );

	if( read_count != (ssize_t) 24 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data at offset: 0 (0x00000000).",
		 function );

		return( -1 );
	}
	if( libwtcdb_file_header_read_data(
	     file_header,
	     file_header_data,
	     24,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

