/*
 * Cache entry functions
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libwtcdb_debug.h"
#include "libwtcdb_definitions.h"
#include "libwtcdb_index_entry.h"
#include "libwtcdb_io_handle.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libcerror.h"
#include "libwtcdb_libcnotify.h"
#include "libwtcdb_libfdatetime.h"

#include "wtcdb_index_entry.h"

/* Creates a index entry
 * Make sure the value index_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_index_entry_initialize(
     libwtcdb_index_entry_t **index_entry,
     libcerror_error_t **error )
{
	static char *function = "libwtcdb_index_entry_initialize";

	if( index_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid index entry.",
		 function );

		return( -1 );
	}
	if( *index_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid index entry value already set.",
		 function );

		return( -1 );
	}
	*index_entry = memory_allocate_structure(
	                libwtcdb_index_entry_t );

	if( *index_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create index entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *index_entry,
	     0,
	     sizeof( libwtcdb_index_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear index entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *index_entry != NULL )
	{
		memory_free(
		 *index_entry );

		*index_entry = NULL;
	}
	return( -1 );
}

/* Frees a index entry
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_index_entry_free(
     libwtcdb_index_entry_t **index_entry,
     libcerror_error_t **error )
{
	static char *function = "libwtcdb_index_entry_free";

	if( index_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid index entry.",
		 function );

		return( -1 );
	}
	if( *index_entry != NULL )
	{
		memory_free(
		 *index_entry );

		*index_entry = NULL;
	}
	return( 1 );
}

/* Reads an index entry
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_index_entry_read_data(
     libwtcdb_index_entry_t *index_entry,
     libwtcdb_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function        = "libwtcdb_index_entry_read_data";
	size_t index_entry_data_size = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit         = 0;
#endif

	if( index_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid index entry.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->file_type != LIBWTCDB_FILE_TYPE_INDEX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported file type.",
		 function );

		return( -1 );
	}
	if( ( io_handle->format_version != 20 )
	 && ( io_handle->format_version != 21 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported format version: %" PRIu32 ".",
		 function,
		 io_handle->format_version );

		return( -1 );
	}
	if( io_handle->format_version == 20 )
	{
		index_entry_data_size = sizeof( wtcdb_index_entry_vista_t );
	}
	else if( io_handle->format_version == 21 )
	{
		index_entry_data_size = sizeof( wtcdb_index_entry_win7_t );
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
	if( data_size < index_entry_data_size )
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
		 "%s: index entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint64_little_endian(
	 ( (wtcdb_index_entry_vista_t *) data )->entry_hash,
	 index_entry->hash );

	if( io_handle->format_version == 20 )
	{
		byte_stream_copy_to_uint64_little_endian(
		 ( (wtcdb_index_entry_vista_t *) data )->modification_time,
		 index_entry->modification_time );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: entry hash\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 index_entry->hash );

		if( io_handle->format_version == 20 )
		{
			if( libwtcdb_debug_print_filetime_value(
			     function,
			     "modification time\t\t\t",
			     ( (wtcdb_index_entry_vista_t *) data )->modification_time,
			     8,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print FILETIME value.",
				 function );

				return( -1 );
			}
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_vista_t *) data )->flags,
			 value_32bit );
		}
		else if( io_handle->format_version == 21 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_win7_t *) data )->flags,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: flags\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( io_handle->format_version == 20 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_vista_t *) data )->cache_entry_offset_32,
			 value_32bit );
		}
		else if( io_handle->format_version == 21 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_win7_t *) data )->cache_entry_offset_32,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: cache entry offset 32\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( io_handle->format_version == 20 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_vista_t *) data )->cache_entry_offset_96,
			 value_32bit );
		}
		else if( io_handle->format_version == 21 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_win7_t *) data )->cache_entry_offset_96,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: cache entry offset 96\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( io_handle->format_version == 20 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_vista_t *) data )->cache_entry_offset_256,
			 value_32bit );
		}
		else if( io_handle->format_version == 21 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_win7_t *) data )->cache_entry_offset_256,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: cache entry offset 256\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( io_handle->format_version == 20 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_vista_t *) data )->cache_entry_offset_1024,
			 value_32bit );
		}
		else if( io_handle->format_version == 21 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_win7_t *) data )->cache_entry_offset_1024,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: cache entry offset 1024\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( io_handle->format_version == 20 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_vista_t *) data )->cache_entry_offset_sr,
			 value_32bit );
		}
		else if( io_handle->format_version == 21 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_index_entry_win7_t *) data )->cache_entry_offset_sr,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: cache entry offset sr\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	index_entry->data_size = index_entry_data_size;

	return( 1 );
}

/* Reads an index entry
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_index_entry_read_file_io_handle(
     libwtcdb_index_entry_t *index_entry,
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t index_entry_data[ 40 ];

	static char *function        = "libwtcdb_index_entry_read_file_io_handle";
	size_t index_entry_data_size = 0;
	ssize_t read_count           = 0;

	if( index_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid index entry.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->file_type != LIBWTCDB_FILE_TYPE_INDEX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported file type.",
		 function );

		return( -1 );
	}
	if( ( io_handle->format_version != 20 )
	 && ( io_handle->format_version != 21 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported format version: %" PRIu32 ".",
		 function,
		 io_handle->format_version );

		return( -1 );
	}
	if( io_handle->format_version == 20 )
	{
		index_entry_data_size = sizeof( wtcdb_index_entry_vista_t );
	}
	else if( io_handle->format_version == 21 )
	{
		index_entry_data_size = sizeof( wtcdb_index_entry_win7_t );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading index entry at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek index entry offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              index_entry_data,
	              index_entry_data_size,
	              error );

	if( read_count != (ssize_t) index_entry_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read index entry data.",
		 function );

		return( -1 );
	}
	if( libwtcdb_index_entry_read_data(
	     index_entry,
	     io_handle,
	     index_entry_data,
	     index_entry_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read index entry.",
		 function );

		return( -1 );
	}
	return( 1 );
}

