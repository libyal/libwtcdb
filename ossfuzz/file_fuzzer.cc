/*
 * OSS-Fuzz target for libwtcdb file type
 *
 * Copyright (C) 2010-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libwtcdb.h"

#if !defined( LIBWTCDB_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBWTCDB_EXTERN \
int libwtcdb_file_open_file_io_handle(
      libwtcdb_file_t *file,
      libbfio_handle_t *file_io_handle,
      int access_flags,
      libwtcdb_error_t **error );

#endif /* !defined( LIBWTCDB_HAVE_BFIO ) */

/* Limits on the number of items to query
 */
#define FUZZER_ITEMS_LIMIT	8

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	libbfio_handle_t *file_io_handle = NULL;
	libwtcdb_file_t *file            = NULL;
	libwtcdb_item_t *item            = NULL;
	uint8_t file_type                = 0;
	int item_index                   = 0;
	int number_of_items              = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libwtcdb_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libwtcdb_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBWTCDB_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libwtcdb_file;
	}
	libwtcdb_file_get_type(
	 file,
	 &file_type,
	 NULL );
	libwtcdb_file_signal_abort(
	 file,
	 NULL );
	if( libwtcdb_file_get_number_of_items(
	     file,
	     &number_of_items,
	     NULL ) == 1 )
	{
		for( item_index = 0;
		     item_index < number_of_items;
		     item_index++ )
		{
			if( item_index >= FUZZER_ITEMS_LIMIT )
			{
				break;
			}
			item = NULL;
			libwtcdb_file_get_item(
			 file,
			 item_index,
			 &item,
			 NULL );
			if( item != NULL )
			{
				libwtcdb_item_free(
				 &item,
				 NULL );
			}
		}
		/* Attempt to retrieve an item using an out of range index
		 * to trigger the validation
		 */
		item = NULL;
		libwtcdb_file_get_item(
		 file,
		 number_of_items,
		 &item,
		 NULL );
		if( item != NULL )
		{
			libwtcdb_item_free(
			 &item,
			 NULL );
		}
	}
	libwtcdb_file_close(
	 file,
	 NULL );
	/* Attempt to open with unsupported access flags
	 * to trigger the validation
	 */
	libwtcdb_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 LIBWTCDB_OPEN_READ_WRITE,
	 NULL );
	libwtcdb_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 0,
	 NULL );
	libwtcdb_file_close(
	 file,
	 NULL );

on_error_libwtcdb_file:
	libwtcdb_file_free(
	 &file,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
