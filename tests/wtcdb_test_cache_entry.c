/*
 * Library cache_entry type test program
 *
 * Copyright (C) 2009-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "wtcdb_test_libbfio.h"
#include "wtcdb_test_libcerror.h"
#include "wtcdb_test_libwtcdb.h"
#include "wtcdb_test_macros.h"
#include "wtcdb_test_memory.h"
#include "wtcdb_test_unused.h"

#include "../libwtcdb/libwtcdb_cache_entry.h"
#include "../libwtcdb/libwtcdb_io_handle.h"

uint8_t wtcdb_test_cache_entry_data1[ 88 ] = {
	0x43, 0x4d, 0x4d, 0x4d, 0x58, 0x00, 0x00, 0x00, 0x16, 0xd7, 0xf9, 0x93, 0xb2, 0x27, 0x26, 0xd5,
	0x6c, 0x00, 0x6e, 0x00, 0x6b, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x74, 0xf9, 0xe6, 0x9c, 0x7c, 0x32, 0x07, 0xf0, 0x35, 0x00, 0x33, 0x00, 0x36, 0x00, 0x31, 0x00,
	0x38, 0x00, 0x64, 0x00, 0x61, 0x00, 0x38, 0x00, 0x32, 0x00, 0x62, 0x00, 0x65, 0x00, 0x64, 0x00,
	0x37, 0x00, 0x38, 0x00, 0x66, 0x00, 0x62, 0x00 };

uint8_t wtcdb_test_cache_entry_data2[ 80 ] = {
	0x43, 0x4d, 0x4d, 0x4d, 0x50, 0x00, 0x00, 0x00, 0x5e, 0x04, 0xf2, 0x17, 0x05, 0x50, 0x2e, 0xaa,
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd, 0x12, 0xe4, 0xac, 0x7a, 0xe1, 0xa2, 0xec,
	0x61, 0x00, 0x61, 0x00, 0x32, 0x00, 0x65, 0x00, 0x35, 0x00, 0x30, 0x00, 0x30, 0x00, 0x35, 0x00,
	0x31, 0x00, 0x37, 0x00, 0x66, 0x00, 0x32, 0x00, 0x30, 0x00, 0x34, 0x00, 0x35, 0x00, 0x65, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT )

/* Tests the libwtcdb_cache_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_cache_entry_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	libwtcdb_cache_entry_t *cache_entry = NULL;
	int result                        = 0;

#if defined( HAVE_WTCDB_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = libwtcdb_cache_entry_initialize(
	          &cache_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "cache_entry",
	 cache_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_cache_entry_free(
	          &cache_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "cache_entry",
	 cache_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwtcdb_cache_entry_initialize(
	          NULL,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	cache_entry = (libwtcdb_cache_entry_t *) 0x12345678UL;

	result = libwtcdb_cache_entry_initialize(
	          &cache_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	cache_entry = NULL;

#if defined( HAVE_WTCDB_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwtcdb_cache_entry_initialize with malloc failing
		 */
		wtcdb_test_malloc_attempts_before_fail = test_number;

		result = libwtcdb_cache_entry_initialize(
		          &cache_entry,
		          &error );

		if( wtcdb_test_malloc_attempts_before_fail != -1 )
		{
			wtcdb_test_malloc_attempts_before_fail = -1;

			if( cache_entry != NULL )
			{
				libwtcdb_cache_entry_free(
				 &cache_entry,
				 NULL );
			}
		}
		else
		{
			WTCDB_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			WTCDB_TEST_ASSERT_IS_NULL(
			 "cache_entry",
			 cache_entry );

			WTCDB_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libwtcdb_cache_entry_initialize with memset failing
		 */
		wtcdb_test_memset_attempts_before_fail = test_number;

		result = libwtcdb_cache_entry_initialize(
		          &cache_entry,
		          &error );

		if( wtcdb_test_memset_attempts_before_fail != -1 )
		{
			wtcdb_test_memset_attempts_before_fail = -1;

			if( cache_entry != NULL )
			{
				libwtcdb_cache_entry_free(
				 &cache_entry,
				 NULL );
			}
		}
		else
		{
			WTCDB_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			WTCDB_TEST_ASSERT_IS_NULL(
			 "cache_entry",
			 cache_entry );

			WTCDB_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_WTCDB_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( cache_entry != NULL )
	{
		libwtcdb_cache_entry_free(
		 &cache_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwtcdb_cache_entry_free function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_cache_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwtcdb_cache_entry_free(
	          NULL,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwtcdb_cache_entry_header_read_data function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_cache_entry_header_read_data(
     void )
{
	libcerror_error_t *error            = NULL;
	libwtcdb_cache_entry_t *cache_entry = NULL;
	libwtcdb_io_handle_t *io_handle     = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libwtcdb_io_handle_initialize(
	          &io_handle,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_cache_entry_initialize(
	          &cache_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "cache_entry",
	 cache_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	io_handle->file_type      = LIBWTCDB_FILE_TYPE_CACHE;
	io_handle->format_version = 20;

	result = libwtcdb_cache_entry_header_read_data(
	          cache_entry,
	          io_handle,
	          wtcdb_test_cache_entry_data1,
	          88,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->file_type      = LIBWTCDB_FILE_TYPE_CACHE;
	io_handle->format_version = 21;

	result = libwtcdb_cache_entry_header_read_data(
	          cache_entry,
	          io_handle,
	          wtcdb_test_cache_entry_data2,
	          80,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwtcdb_cache_entry_header_read_data(
	          NULL,
	          io_handle,
	          wtcdb_test_cache_entry_data1,
	          88,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwtcdb_cache_entry_header_read_data(
	          cache_entry,
	          NULL,
	          wtcdb_test_cache_entry_data1,
	          88,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	io_handle->file_type      = LIBWTCDB_FILE_TYPE_INDEX;
	io_handle->format_version = 20;

	result = libwtcdb_cache_entry_header_read_data(
	          cache_entry,
	          io_handle,
	          wtcdb_test_cache_entry_data1,
	          88,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	io_handle->file_type      = LIBWTCDB_FILE_TYPE_CACHE;
	io_handle->format_version = 0;

	result = libwtcdb_cache_entry_header_read_data(
	          cache_entry,
	          io_handle,
	          wtcdb_test_cache_entry_data1,
	          88,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwtcdb_cache_entry_header_read_data(
	          cache_entry,
	          io_handle,
	          NULL,
	          88,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwtcdb_cache_entry_header_read_data(
	          cache_entry,
	          io_handle,
	          wtcdb_test_cache_entry_data1,
	          0,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwtcdb_cache_entry_header_read_data(
	          cache_entry,
	          io_handle,
	          wtcdb_test_cache_entry_data1,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libwtcdb_cache_entry_free(
	          &cache_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "cache_entry",
	 cache_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_io_handle_free(
	          &io_handle,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( cache_entry != NULL )
	{
		libwtcdb_cache_entry_free(
		 &cache_entry,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libwtcdb_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwtcdb_cache_entry_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_cache_entry_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle    = NULL;
	libcerror_error_t *error            = NULL;
	libwtcdb_cache_entry_t *cache_entry = NULL;
	libwtcdb_io_handle_t *io_handle     = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libwtcdb_io_handle_initialize(
	          &io_handle,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_memory_range_initialize(
	          &file_io_handle,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_memory_range_set(
	          file_io_handle,
	          wtcdb_test_cache_entry_data1,
	          88,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_open(
	          file_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_cache_entry_initialize(
	          &cache_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "cache_entry",
	 cache_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	io_handle->file_type      = LIBWTCDB_FILE_TYPE_CACHE;
	io_handle->format_version = 20;

	result = libwtcdb_cache_entry_read_file_io_handle(
	          cache_entry,
	          io_handle,
	          file_io_handle,
	          0,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwtcdb_cache_entry_read_file_io_handle(
	          NULL,
	          io_handle,
	          file_io_handle,
	          0,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwtcdb_cache_entry_read_file_io_handle(
	          cache_entry,
	          NULL,
	          file_io_handle,
	          0,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	io_handle->file_type      = LIBWTCDB_FILE_TYPE_INDEX;
	io_handle->format_version = 20;

	result = libwtcdb_cache_entry_read_file_io_handle(
	          cache_entry,
	          io_handle,
	          file_io_handle,
	          0,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	io_handle->file_type      = LIBWTCDB_FILE_TYPE_CACHE;
	io_handle->format_version = 0;

	result = libwtcdb_cache_entry_read_file_io_handle(
	          cache_entry,
	          io_handle,
	          file_io_handle,
	          0,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwtcdb_cache_entry_read_file_io_handle(
	          cache_entry,
	          io_handle,
	          NULL,
	          0,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libwtcdb_cache_entry_free(
	          &cache_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "cache_entry",
	 cache_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_close(
	          file_io_handle,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "file_io_handle",
	 file_io_handle );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( cache_entry != NULL )
	{
		libwtcdb_cache_entry_free(
		 &cache_entry,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libwtcdb_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc WTCDB_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] WTCDB_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc WTCDB_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] WTCDB_TEST_ATTRIBUTE_UNUSED )
#endif
{
	WTCDB_TEST_UNREFERENCED_PARAMETER( argc )
	WTCDB_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT )

	WTCDB_TEST_RUN(
	 "libwtcdb_cache_entry_initialize",
	 wtcdb_test_cache_entry_initialize );

	WTCDB_TEST_RUN(
	 "libwtcdb_cache_entry_free",
	 wtcdb_test_cache_entry_free );

	WTCDB_TEST_RUN(
	 "libwtcdb_cache_entry_header_read_data",
	 wtcdb_test_cache_entry_header_read_data );

	WTCDB_TEST_RUN(
	 "libwtcdb_cache_entry_read_file_io_handle",
	 wtcdb_test_cache_entry_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

