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
#include "libwtcdb_debug.h"
#include "libwtcdb_definitions.h"
#include "libwtcdb_io_handle.h"
#include "libwtcdb_libbfio.h"
#include "libwtcdb_libfdatetime.h"
#include "libwtcdb_libfvalue.h"
#include "libwtcdb_value_identifier.h"

#include "wtcdb_file_header.h"
#include "wtcdb_thumbnail_entry.h"

const uint8_t *wtcdb_database_file_signature = (uint8_t *) "CMMM";
const uint8_t *wtcdb_index_file_signature    = (uint8_t *) "IMMM";

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
     uint32_t *first_thumbnail_entry_offset,
     uint32_t *number_of_thumbnail_entries,
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
	if( number_of_thumbnail_entries == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of thumbnail entries.",
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
	     wtcdb_database_file_signature,
	     4 ) != 0 )
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
	 file_header.first_thumbnail_entry_offset,
	 *first_thumbnail_entry_offset );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.number_of_thumbnail_entries,
	 *number_of_thumbnail_entries );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 file_header.signature[ 0 ],
		 file_header.signature[ 1 ],
		 file_header.signature[ 2 ],
		 file_header.signature[ 3 ] );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.version,
		 value_32bit );
		libnotify_printf(
		 "%s: version\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.cache_type,
		 value_32bit );
		libnotify_printf(
		 "%s: cache type\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libnotify_printf(
		 "%s: first thumbnail entry offset\t: 0x%08" PRIx32 "\n",
		 function,
		 *first_thumbnail_entry_offset );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.next_thumbnail_entry_offset,
		 value_32bit );
		libnotify_printf(
		 "%s: next thumbnail entry offset\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libnotify_printf(
		 "%s: number of thumbnail entries\t: %" PRIu32 "\n",
		 function,
		 *number_of_thumbnail_entries );

		libnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Reads the items into the items array
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_io_handle_read_items(
     libwtcdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t first_thumbnail_entry_offset,
     uint32_t number_of_items,
     libwtcdb_array_t *items_array,
     liberror_error_t **error )
{
	wtcdb_thumbnail_entry_t thumbnail_entry;

	libfvalue_table_t *values_table = NULL;
	static char *function           = "libwtcdb_io_handle_read_items";
	ssize_t read_count              = 0;
	uint32_t data_size              = 0;
	uint32_t identifier_string_size = 0;
	uint32_t item_iterator          = 0;
	uint32_t thumbnail_entry_size   = 0;
	int item_entry_index            = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit            = 0;
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
	for( item_iterator = 0;
	     item_iterator < number_of_items;
	     item_iterator++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: reading thumbnail entry: %" PRIu32 " at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
			 function,
			 item_iterator,
			 first_thumbnail_entry_offset,
			 first_thumbnail_entry_offset );
		}
#endif
		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     (off64_t) first_thumbnail_entry_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek thumbnail entry: %" PRIu32 " offset: %" PRIu32 ".",
			 function,
			 item_iterator,
			 first_thumbnail_entry_offset );

			return( -1 );
		}
		read_count = libbfio_handle_read(
			      file_io_handle,
			      (uint8_t *) &thumbnail_entry,
			      sizeof( wtcdb_thumbnail_entry_t ),
			      error );

		if( read_count != (ssize_t) sizeof( wtcdb_thumbnail_entry_t ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read thumbnail entry: %" PRIu32 ".",
			 function,
			 item_iterator );

			return( -1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 ":\n",
			 function,
			 item_iterator );
			libnotify_print_data(
			 (uint8_t *) &thumbnail_entry,
			 sizeof( wtcdb_thumbnail_entry_t ) );
		}
#endif
		if( memory_compare(
		     thumbnail_entry.signature,
		     wtcdb_database_file_signature,
		     4 ) != 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid thumbnail entry: %" PRIu32 " signature.",
			 function,
			 item_iterator );

			return( -1 );
		}
		byte_stream_copy_to_uint32_little_endian(
		 thumbnail_entry.size,
		 thumbnail_entry_size );

		byte_stream_copy_to_uint32_little_endian(
		 thumbnail_entry.identifier_string_size,
		 identifier_string_size );

		byte_stream_copy_to_uint32_little_endian(
		 thumbnail_entry.data_size,
		 data_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " signature\t\t\t: %c%c%c%c\n",
			 function,
			 item_iterator,
			 thumbnail_entry.signature[ 0 ],
			 thumbnail_entry.signature[ 1 ],
			 thumbnail_entry.signature[ 2 ],
			 thumbnail_entry.signature[ 3 ] );

			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " size\t\t\t: %" PRIu32 "\n",
			 function,
			 item_iterator,
			 thumbnail_entry_size );

/* TODO add values */

			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " identifier string size\t: %" PRIu32 "\n",
			 function,
			 item_iterator,
			 identifier_string_size );

			byte_stream_copy_to_uint32_little_endian(
			 thumbnail_entry.unknown2,
			 value_32bit );
			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " unknown2\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 item_iterator,
			 value_32bit );

			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " data size\t\t\t: %" PRIu32 "\n",
			 function,
			 item_iterator,
			 data_size );

			byte_stream_copy_to_uint32_little_endian(
			 thumbnail_entry.unknown3,
			 value_32bit );
			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " unknown3\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 item_iterator,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 thumbnail_entry.unknown4,
			 value_32bit );
			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " unknown4\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 item_iterator,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 thumbnail_entry.unknown5,
			 value_32bit );
			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " unknown5\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 item_iterator,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 thumbnail_entry.unknown6,
			 value_32bit );
			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " unknown6\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 item_iterator,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 thumbnail_entry.unknown7,
			 value_32bit );
			libnotify_printf(
			 "%s: thumbnail entry: %03" PRIu32 " unknown7\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 item_iterator,
			 value_32bit );

			libnotify_printf(
			 "\n" );
		}
#endif
		/* TODO boundary check string size with thumbnail_entry_size */

		/* TODO read identifier string */

		/* TODO print padding */

		/* TODO boundary check data size with thumbnail_entry_size */

		/* TODO put data offset in runtime thumbnail entry */

		/* TODO replace by set entry ? */
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

			libfvalue_table_free(
			 (intptr_t *) values_table,
			 error );

			return( -1 );
		}
		values_table = NULL;

		if( ( sizeof( wtcdb_thumbnail_entry_t ) + identifier_string_size + data_size ) != thumbnail_entry_size )
		{
fprintf( stderr, "SIZE MISMATCH: %zd != %zd\n",
 sizeof( wtcdb_thumbnail_entry_t ) + identifier_string_size + data_size,
 thumbnail_entry_size );
		}


		first_thumbnail_entry_offset += thumbnail_entry_size;
	}
	return( 1 );
}

