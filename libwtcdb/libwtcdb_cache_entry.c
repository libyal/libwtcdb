/*
 * Cache entry functions
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

#include "libwtcdb_cache_entry.h"
#include "libwtcdb_crc.h"
#include "libwtcdb_debug.h"
#include "libwtcdb_definitions.h"
#include "libwtcdb_io_handle.h"
#include "libwtcdb_libcerror.h"
#include "libwtcdb_libcnotify.h"
#include "libwtcdb_libuna.h"
#include "libwtcdb_types.h"

#include "wtcdb_cache_entry.h"

/* Creates a cache entry
 * Make sure the value cache_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_cache_entry_initialize(
     libwtcdb_cache_entry_t **cache_entry,
     libcerror_error_t **error )
{
	static char *function = "libwtcdb_cache_entry_initialize";

	if( cache_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache entry.",
		 function );

		return( -1 );
	}
	if( *cache_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid cache entry value already set.",
		 function );

		return( -1 );
	}
	*cache_entry = memory_allocate_structure(
	                libwtcdb_cache_entry_t );

	if( *cache_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create cache entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *cache_entry,
	     0,
	     sizeof( libwtcdb_cache_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear cache entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *cache_entry != NULL )
	{
		memory_free(
		 *cache_entry );

		*cache_entry = NULL;
	}
	return( -1 );
}

/* Frees a cache entry
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_cache_entry_free(
     libwtcdb_cache_entry_t **cache_entry,
     libcerror_error_t **error )
{
	static char *function = "libwtcdb_cache_entry_free";

	if( cache_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache entry.",
		 function );

		return( -1 );
	}
	if( *cache_entry != NULL )
	{
		if( ( *cache_entry )->identifier != NULL )
		{
			memory_free(
			 ( *cache_entry )->identifier );
		}
		memory_free(
		 *cache_entry );

		*cache_entry = NULL;
	}
	return( 1 );
}

/* Reads the cache entry data
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_cache_entry_read_data(
     libwtcdb_cache_entry_t *cache_entry,
     libwtcdb_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function          = "libwtcdb_cache_entry_read_data";
	size_t cache_entry_header_size = 0;
	size_t data_offset             = 0;
	uint64_t calculated_crc        = 0;
	uint64_t stored_data_crc       = 0;
	uint64_t stored_header_crc     = 0;
	uint32_t cached_data_size      = 0;
	uint32_t cache_entry_size      = 0;
	uint32_t identifier_size       = 0;
	uint32_t padding_size          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit           = 0;
	uint32_t value_32bit           = 0;
#endif

	if( cache_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache entry.",
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
	if( io_handle->file_type != LIBWTCDB_FILE_TYPE_CACHE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported file type.",
		 function );

		return( -1 );
	}
	if( ( io_handle->version != 20 )
	 && ( io_handle->version != 21 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported format version: %" PRIu32 ".",
		 function,
		 io_handle->version );

		return( -1 );
	}
	if( io_handle->version == 20 )
	{
		cache_entry_header_size = sizeof( wtcdb_cache_entry_vista_t );
	}
	else if( io_handle->version == 21 )
	{
		cache_entry_header_size = sizeof( wtcdb_cache_entry_win7_t );
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
	if( data_size < cache_entry_header_size )
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
		 "%s: cache entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (wtcdb_cache_entry_vista_t *) data )->signature,
	     wtcdb_cache_file_signature,
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (wtcdb_cache_entry_vista_t *) data )->size,
	 cache_entry_size );

	if( io_handle->version == 20 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_entry_vista_t *) data )->identifier_string_size,
		 identifier_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_entry_vista_t *) data )->padding_size,
		 padding_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_entry_vista_t *) data )->data_size,
		 cached_data_size );

		byte_stream_copy_to_uint64_little_endian(
		 ( (wtcdb_cache_entry_vista_t *) data )->header_checksum,
		 stored_header_crc );

		byte_stream_copy_to_uint64_little_endian(
		 ( (wtcdb_cache_entry_vista_t *) data )->data_checksum,
		 stored_data_crc );
	}
	else if( io_handle->version == 21 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_entry_win7_t *) data )->identifier_string_size,
		 identifier_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_entry_win7_t *) data )->padding_size,
		 padding_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_entry_win7_t *) data )->data_size,
		 cached_data_size );

		byte_stream_copy_to_uint64_little_endian(
		 ( (wtcdb_cache_entry_win7_t *) data )->data_checksum,
		 stored_data_crc );

		byte_stream_copy_to_uint64_little_endian(
		 ( (wtcdb_cache_entry_win7_t *) data )->header_checksum,
		 stored_header_crc );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: %c%c%c%c\n",
		 function,
		 ( (wtcdb_cache_entry_vista_t *) data )->signature[ 0 ],
		 ( (wtcdb_cache_entry_vista_t *) data )->signature[ 1 ],
		 ( (wtcdb_cache_entry_vista_t *) data )->signature[ 2 ],
		 ( (wtcdb_cache_entry_vista_t *) data )->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 cache_entry_size );

		byte_stream_copy_to_uint64_little_endian(
		 ( (wtcdb_cache_entry_vista_t *) data )->entry_hash,
		 value_64bit );
		libcnotify_printf(
		 "%s: entry hash\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( io_handle->version == 20 )
		{
/* TODO make a string of this ?*/
			libcnotify_printf(
			 "%s: file extension\t\t\t: ",
			 function );

			if( ( (wtcdb_cache_entry_vista_t *) data )->file_extension[ 0 ] == 0 )
			{
				libcnotify_printf(
				 "(none)" );
			}
			else
			{
				libcnotify_printf(
				 "%c",
				 ( (wtcdb_cache_entry_vista_t *) data )->file_extension[ 0 ] );
			}
			if( ( (wtcdb_cache_entry_vista_t *) data )->file_extension[ 2 ] != 0 )
			{
				libcnotify_printf(
				 "%c",
				 ( (wtcdb_cache_entry_vista_t *) data )->file_extension[ 2 ] );
			}
			if( ( (wtcdb_cache_entry_vista_t *) data )->file_extension[ 4 ] != 0 )
			{
				libcnotify_printf(
				 "%c",
				 ( (wtcdb_cache_entry_vista_t *) data )->file_extension[ 4 ] );
			}
			if( ( (wtcdb_cache_entry_vista_t *) data )->file_extension[ 6 ] != 0 )
			{
				libcnotify_printf(
				 "%c",
				 ( (wtcdb_cache_entry_vista_t *) data )->file_extension[ 6 ] );
			}
			libcnotify_printf(
			 "\n" );
		}
		libcnotify_printf(
		 "%s: identifier string size\t\t: %" PRIu32 "\n",
		 function,
		 identifier_size );

		libcnotify_printf(
		 "%s: padding size\t\t\t: %" PRIu32 "\n",
		 function,
		 padding_size );

		libcnotify_printf(
		 "%s: data size\t\t\t: %" PRIu32 "\n",
		 function,
		 cached_data_size );

		if( io_handle->version == 20 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_cache_entry_vista_t *) data )->unknown1,
			 value_32bit );
		}
		else if( io_handle->version == 21 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_cache_entry_win7_t *) data )->unknown1,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown1\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: data checksum\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 stored_data_crc );

		libcnotify_printf(
		 "%s: header checksum\t\t: 0x%08" PRIx64 "\n",
		 function,
		 stored_header_crc );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( ( cache_entry_size < cache_entry_header_size )
	 || ( cache_entry_size > data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid cache entry size value out of bounds.",
		 function );

		return( -1 );
	}
	if( libwtcdb_crc64_weak_calculate(
	     &calculated_crc,
	     data,
	     cache_entry_size - 8,
	     (uint64_t) -1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unable to calculate CRC-64.",
		 function );

		return( -1 );
	}
	if( stored_header_crc != calculated_crc )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: mismatch in header CRC-64 ( 0x%08" PRIx64 " != 0x%08" PRIx64 " ).\n",
			 function,
			 stored_header_crc,
			 calculated_crc );
		}
#endif
	}
	data_offset = cache_entry_header_size;

	if( identifier_size > 0 )
	{
		if( ( identifier_size > cache_entry_size )
		 || ( data_offset > ( cache_entry_size - identifier_size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid identifier size value out of bounds.",
			 function );

			return( -1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: identifier string data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 identifier_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libwtcdb_debug_print_utf16_string_value(
			     function,
			     "identifier string\t\t\t",
			     &( data[ data_offset ] ),
			     identifier_size,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print UTF-16 string value.",
				 function );

				return( -1 );
			}
		}
#endif
		data_offset += identifier_size;
	}
	if( padding_size > 0 )
	{
		if( ( padding_size > cache_entry_size )
		 || ( data_offset > ( cache_entry_size - padding_size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid padding size value out of bounds.",
			 function );

			return( -1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: padding data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 padding_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
		data_offset += padding_size;
	}
	return( 1 );
}

