/*
 * Input/Output (IO) handle functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>
#include <libnotify.h>

#include "libwtcdb_array_type.h"
#include "libwtcdb_crc.h"
#include "libwtcdb_debug.h"
#include "libwtcdb_definitions.h"
#include "libwtcdb_io_handle.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libfvalue.h"
#include "libwtcdb_libuna.h"
#include "libwtcdb_value_identifier.h"

#include "wtcdb_cache_entry.h"
#include "wtcdb_file_header.h"

const uint8_t *wtcdb_cache_file_signature = (uint8_t *) "CMMM";
const uint8_t *wtcdb_index_file_signature = (uint8_t *) "IMMM";

/* Initialize an IO handle
 * Make sure the value io_handle is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_io_handle_initialize(
     libwtcdb_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "libwtcdb_io_handle_initialize";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle == NULL )
	{
		*io_handle = (libwtcdb_io_handle_t *) memory_allocate(
		                                       sizeof( libwtcdb_io_handle_t ) );

		if( *io_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create IO handle.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *io_handle,
		     0,
		     sizeof( libwtcdb_io_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file.",
			 function );

			memory_free(
			 *io_handle );

			*io_handle = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees an exisisting IO handle
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_io_handle_free(
     libwtcdb_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "libwtcdb_io_handle_free";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_io_handle_read_file_header(
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *first_cache_entry_offset,
     uint32_t *available_cache_entry_offset,
     uint32_t *number_of_cache_entries,
     liberror_error_t **error )
{
	wtcdb_file_header_t file_header;

	static char *function = "libwtcdb_io_handle_read_file_header";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( first_cache_entry_offset == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first cache entry offset.",
		 function );

		return( -1 );
	}
	if( available_cache_entry_offset == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid available cache entry offset.",
		 function );

		return( -1 );
	}
	if( number_of_cache_entries == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of cache entries.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              (uint8_t *) &file_header,
	              sizeof( wtcdb_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( wtcdb_file_header_t ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: file header:\n",
		 function );
		libnotify_print_data(
		 (uint8_t *) &file_header,
		 sizeof( wtcdb_file_header_t ) );
	}
#endif
	if( memory_compare(
	     file_header.signature,
	     wtcdb_cache_file_signature,
	     4 ) == 0 )
	{
		io_handle->file_type = LIBWTCDB_FILE_TYPE_CACHE;
	}
	else if( memory_compare(
	          file_header.signature,
	          wtcdb_index_file_signature,
	          4 ) == 0 )
	{
		io_handle->file_type = LIBWTCDB_FILE_TYPE_INDEX;
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 file_header.version,
	 io_handle->version );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.first_cache_entry_offset,
	 *first_cache_entry_offset );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.available_cache_entry_offset,
	 *available_cache_entry_offset );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.number_of_cache_entries,
	 *number_of_cache_entries );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: signature\t\t\t\t\t: %c%c%c%c\n",
		 function,
		 file_header.signature[ 0 ],
		 file_header.signature[ 1 ],
		 file_header.signature[ 2 ],
		 file_header.signature[ 3 ] );

		libnotify_printf(
		 "%s: version\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 io_handle->version );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.cache_type,
		 value_32bit );
		libnotify_printf(
		 "%s: cache type\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libnotify_printf(
		 "%s: first cache entry offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 *first_cache_entry_offset );

		libnotify_printf(
		 "%s: available cache entry offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 *available_cache_entry_offset );

		libnotify_printf(
		 "%s: number of cache entries\t\t: %" PRIu32 "\n",
		 function,
		 *number_of_cache_entries );

		libnotify_printf(
		 "\n" );
	}
#endif
	if( ( io_handle->version != 20 )
	 && ( io_handle->version != 21 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported version: %" PRIu32 ".",
		 function,
		 io_handle->version );

		return( -1 );
	}
	return( 1 );
}

/* Reads the items into the items array
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_io_handle_read_items(
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t first_cache_entry_offset,
     uint32_t available_cache_entry_offset,
     uint32_t number_of_items,
     libwtcdb_array_t *items_array,
     liberror_error_t **error )
{
	uint8_t *cache_entry_data                   = NULL;
	uint8_t *identifier_string_data             = NULL;
	static char *function                       = "libwtcdb_io_handle_read_items";
	size_t read_size                            = 0;
	ssize_t read_count                          = 0;
	uint64_t calculated_crc                     = 0;
	uint64_t stored_data_crc                    = 0;
	uint64_t stored_header_crc                  = 0;
	uint32_t data_size                          = 0;
	uint32_t identifier_string_size             = 0;
	uint32_t item_iterator                      = 0;
	uint32_t padding_size                       = 0;
	uint32_t cache_entry_offset                 = 0;
	uint32_t cache_entry_size                   = 0;
	int item_entry_index                        = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t *value_string = NULL;
	size_t value_string_size                    = 0;
	uint64_t value_64bit                        = 0;
	uint32_t value_32bit                        = 0;
	int result                                  = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( ( io_handle->version != 20 )
	 && ( io_handle->version != 21 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported version: %" PRIu32 ".",
		 function,
		 io_handle->version );

		return( -1 );
	}
	if( items_array == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid items array.",
		 function );

		return( -1 );
	}
	if( io_handle->version == 20 )
	{
		read_size = sizeof( wtcdb_cache_entry_vista_t );
	}
	else if( io_handle->version == 21 )
	{
		read_size = sizeof( wtcdb_cache_entry_win7_t );
	}
	cache_entry_data = (uint8_t *) memory_allocate(
	                                    read_size );

	if( cache_entry_data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create cache entry data.",
		 function );

		return( -1 );
	}
	for( item_iterator = 0;
	     item_iterator < number_of_items;
	     item_iterator++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: reading cache entry: %" PRIu32 " at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
			 function,
			 item_iterator,
			 first_cache_entry_offset,
			 first_cache_entry_offset );
		}
#endif
		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     (off64_t) first_cache_entry_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek cache entry: %" PRIu32 " offset: %" PRIu32 ".",
			 function,
			 item_iterator,
			 first_cache_entry_offset );

			memory_free(
			 cache_entry_data );

			return( -1 );
		}
		read_count = libbfio_handle_read(
			      file_io_handle,
			      cache_entry_data,
			      read_size,
			      error );

		if( read_count != (ssize_t) read_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read cache entry: %" PRIu32 ".",
			 function,
			 item_iterator );

			memory_free(
			 cache_entry_data );

			return( -1 );
		}
		cache_entry_offset = read_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " data:\n",
			 function,
			 item_iterator );
			libnotify_print_data(
			 cache_entry_data,
			 read_size );
		}
#endif
		if( memory_compare(
		     ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->signature,
		     wtcdb_cache_file_signature,
		     4 ) != 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid cache entry: %" PRIu32 " signature.",
			 function,
			 item_iterator );

			memory_free(
			 cache_entry_data );

			return( -1 );
		}
		byte_stream_copy_to_uint32_little_endian(
		 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->size,
		 cache_entry_size );

		if( io_handle->version == 20 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->identifier_string_size,
			 identifier_string_size );

			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->padding_size,
			 padding_size );

			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->data_size,
			 data_size );

			byte_stream_copy_to_uint64_little_endian(
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->header_checksum,
			 stored_header_crc );

			byte_stream_copy_to_uint64_little_endian(
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->data_checksum,
			 stored_data_crc );
		}
		else if( io_handle->version == 21 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_cache_entry_win7_t *) cache_entry_data )->identifier_string_size,
			 identifier_string_size );

			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_cache_entry_win7_t *) cache_entry_data )->padding_size,
			 padding_size );

			byte_stream_copy_to_uint32_little_endian(
			 ( (wtcdb_cache_entry_win7_t *) cache_entry_data )->data_size,
			 data_size );

			byte_stream_copy_to_uint64_little_endian(
			 ( (wtcdb_cache_entry_win7_t *) cache_entry_data )->data_checksum,
			 stored_data_crc );

			byte_stream_copy_to_uint64_little_endian(
			 ( (wtcdb_cache_entry_win7_t *) cache_entry_data )->header_checksum,
			 stored_header_crc );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " signature\t\t\t: %c%c%c%c\n",
			 function,
			 item_iterator,
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->signature[ 0 ],
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->signature[ 1 ],
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->signature[ 2 ],
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->signature[ 3 ] );

			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " size\t\t\t: %" PRIu32 "\n",
			 function,
			 item_iterator,
			 cache_entry_size );

			byte_stream_copy_to_uint64_little_endian(
			 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->unknown1,
			 value_64bit );
			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " unknown1\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 item_iterator,
			 value_64bit );

			if( io_handle->version == 20 )
			{
/* TODO make a string of this ?*/
				libnotify_printf(
				 "%s: cache entry: %03" PRIu32 " file extension\t\t: ",
				 function,
				 item_iterator );

				if( ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->file_extension[ 0 ] == 0 )
				{
					libnotify_printf(
					 "(none)" );
				}
				else
				{
					libnotify_printf(
					 "%c",
					 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->file_extension[ 0 ] );
				}
				if( ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->file_extension[ 2 ] != 0 )
				{
					libnotify_printf(
					 "%c",
					 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->file_extension[ 2 ] );
				}
				if( ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->file_extension[ 4 ] != 0 )
				{
					libnotify_printf(
					 "%c",
					 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->file_extension[ 4 ] );
				}
				if( ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->file_extension[ 6 ] != 0 )
				{
					libnotify_printf(
					 "%c",
					 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->file_extension[ 6 ] );
				}
				libnotify_printf(
				 "\n" );
			}

			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " identifier string size\t: %" PRIu32 "\n",
			 function,
			 item_iterator,
			 identifier_string_size );

			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " padding size\t\t: %" PRIu32 "\n",
			 function,
			 item_iterator,
			 padding_size );

			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " data size\t\t\t: %" PRIu32 "\n",
			 function,
			 item_iterator,
			 data_size );

			if( io_handle->version == 20 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (wtcdb_cache_entry_vista_t *) cache_entry_data )->unknown2,
				 value_32bit );
			}
			else if( io_handle->version == 21 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (wtcdb_cache_entry_win7_t *) cache_entry_data )->unknown2,
				 value_32bit );
			}
			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " unknown2\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 item_iterator,
			 value_32bit );

			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " data checksum\t\t: 0x%08" PRIx64 "\n",
			 function,
			 item_iterator,
			 stored_data_crc );

			libnotify_printf(
			 "%s: cache entry: %03" PRIu32 " header checksum\t\t: 0x%08" PRIx64 "\n",
			 function,
			 item_iterator,
			 stored_header_crc );

			libnotify_printf(
			 "\n" );
		}
#endif
		if( libwtcdb_crc64_weak_calculate(
		     &calculated_crc,
		     cache_entry_data,
		     read_size - 8,
		     (uint64_t) -1,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unable to calculate CRC-64.",
			 function );

			return( -1 );
		}
		if( stored_header_crc != calculated_crc )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libnotify_verbose != 0 )
			{
				libnotify_printf(
				 "%s: mismatch in header CRC-64 ( 0x%08" PRIx64 " != 0x%08" PRIx64 " ).\n",
				 function,
				 stored_header_crc,
				 calculated_crc );
			}
#endif
		}
		if( identifier_string_size > 0 )
		{
			if( ( cache_entry_offset + identifier_string_size ) > cache_entry_size )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid identifier string size value exceeds cache entry size.",
				 function );

				memory_free(
				 cache_entry_data );

				return( -1 );
			}
			/* TODO store string in runtime cache entry */
			identifier_string_data = (uint8_t *) memory_allocate(
							      identifier_string_size );

			if( identifier_string_data == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create identifier string data.",
				 function );

				memory_free(
				 cache_entry_data );

				return( -1 );
			}
			read_count = libbfio_handle_read(
				      file_io_handle,
				      identifier_string_data,
				      identifier_string_size,
				      error );

			if( read_count != (ssize_t) identifier_string_size )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read cache entry: %" PRIu32 " identifier string data.",
				 function,
				 item_iterator );

				memory_free(
				 identifier_string_data );
				memory_free(
				 cache_entry_data );

				return( -1 );
			}
			cache_entry_offset += identifier_string_size;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libnotify_verbose != 0 )
			{
				libnotify_printf(
				 "%s: cache entry: %03" PRIu32 " identifier string data:\n",
				 function,
				 item_iterator );
				libnotify_print_data(
				 identifier_string_data,
				 identifier_string_size );
			}
#endif
			/* TODO print formatted identifier string */

#if defined( HAVE_DEBUG_OUTPUT )
			if( libnotify_verbose != 0 )
			{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
				result = libuna_utf16_string_size_from_utf16_stream(
					  identifier_string_data,
					  identifier_string_size,
					  LIBUNA_ENDIAN_LITTLE,
					  &value_string_size,
					  error );
#else
				result = libuna_utf8_string_size_from_utf16_stream(
					  identifier_string_data,
					  identifier_string_size,
					  LIBUNA_ENDIAN_LITTLE,
					  &value_string_size,
					  error );
#endif
				if( result != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to determine size of volume label string.",
					 function );

					memory_free(
					 identifier_string_data );
					memory_free(
					 cache_entry_data );

					return( -1 );
				}
				value_string = (libcstring_system_character_t *) memory_allocate(
				                                                  sizeof( libcstring_system_character_t ) * value_string_size );

				if( value_string == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_MEMORY,
					 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create volume label string.",
					 function );

					memory_free(
					 identifier_string_data );
					memory_free(
					 cache_entry_data );

					return( -1 );
				}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
				result = libuna_utf16_string_copy_from_utf16_stream(
					  (libuna_utf16_character_t *) value_string,
					  value_string_size,
					  identifier_string_data,
					  identifier_string_size,
					  LIBUNA_ENDIAN_LITTLE,
					  error );
#else
				result = libuna_utf8_string_copy_from_utf16_stream(
					  (libuna_utf8_character_t *) value_string,
					  value_string_size,
					  identifier_string_data,
					  identifier_string_size,
					  LIBUNA_ENDIAN_LITTLE,
					  error );
#endif
				if( result != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set volume label string.",
					 function );

					memory_free(
					 value_string );
					memory_free(
					 identifier_string_data );
					memory_free(
					 cache_entry_data );

					return( -1 );
				}
				libnotify_printf(
				 "%s: cache entry: %03" PRIu32 " identifier string\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
				 function,
				 item_iterator,
				 value_string );

				memory_free(
				 value_string );
			}
#endif
			memory_free(
			 identifier_string_data );
		}
		if( padding_size > 0 )
		{
			if( ( cache_entry_offset + padding_size ) > cache_entry_size )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid padding size value exceeds cache entry size.",
				 function );

				memory_free(
				 cache_entry_data );

				return( -1 );
			}
			/* TODO print padding
			cache_entry_offset += padding_size;
			*/

			cache_entry_offset += padding_size;
		}
		if( data_size > 0 )
		{
			if( ( cache_entry_offset + data_size ) > cache_entry_size )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid data size value exceeds cache entry size.",
				 function );

				memory_free(
				 cache_entry_data );

				return( -1 );
			}
			cache_entry_offset += data_size;

		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "\n" );
		}
#endif
		/* TODO put data offset in runtime cache entry */

		if( first_cache_entry_offset == available_cache_entry_offset )
		{
			break;
		}
/* TODO
		if( libwtcdb_array_append_entry(
		     items_array,
		     &item_entry_index,
		     (intptr_t *) values_table,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append item values to items array.",
			 function );

			memory_free(
			 cache_entry_data );

			return( -1 );
		}
		values_table = NULL;
*/

		if( cache_entry_offset != cache_entry_size )
		{
fprintf( stderr, "SIZE MISMATCH: %" PRIu32 " %" PRIu32 "n",
 cache_entry_offset,
 cache_entry_size );
		}

		first_cache_entry_offset += cache_entry_size;
	}
	memory_free(
	 cache_entry_data );

	return( 1 );
}

