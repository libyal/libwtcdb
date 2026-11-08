/*
 * OSS-Fuzz target for libwtcdb cache_entry type
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

#include "../libwtcdb/libwtcdb_cache_entry.h"

/* The cache entry format versions for which distinct header formats exist
 */
static const uint32_t format_versions[ 3 ] = {
	20,
	21,
	30
};

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	libbfio_handle_t *file_io_handle    = NULL;
	libwtcdb_io_handle_t *io_handle     = NULL;
	libwtcdb_cache_entry_t *cache_entry = NULL;
	size_t version_index                = 0;

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
	if( libbfio_handle_open(
	     file_io_handle,
	     LIBBFIO_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libwtcdb_io_handle_initialize(
	     &io_handle,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libwtcdb_cache_entry_initialize(
	     &cache_entry,
	     NULL ) != 1 )
	{
		goto on_error_libwtcdb_io_handle;
	}
	for( version_index = 0;
	     version_index < ( sizeof( format_versions ) / sizeof( format_versions[ 0 ] ) );
	     version_index++ )
	{
		io_handle->file_type      = LIBWTCDB_FILE_TYPE_CACHE;
		io_handle->format_version = format_versions[ version_index ];

		libwtcdb_cache_entry_header_read_data(
		 cache_entry,
		 io_handle,
		 data,
		 size,
		 NULL );
		libwtcdb_cache_entry_read_file_io_handle(
		 cache_entry,
		 io_handle,
		 file_io_handle,
		 0,
		 NULL );
	}

on_error_libwtcdb_cache_entry:
	libwtcdb_cache_entry_free(
	 &cache_entry,
	 NULL );

on_error_libwtcdb_io_handle:
	libwtcdb_io_handle_free(
	 &io_handle,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
