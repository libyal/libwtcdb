/*
 * Library index_entry type test program
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "wtcdb_test_functions.h"
#include "wtcdb_test_libbfio.h"
#include "wtcdb_test_libcerror.h"
#include "wtcdb_test_libwtcdb.h"
#include "wtcdb_test_macros.h"
#include "wtcdb_test_memory.h"
#include "wtcdb_test_unused.h"

#include "../libwtcdb/libwtcdb_index_entry.h"
#include "../libwtcdb/libwtcdb_io_handle.h"

uint8_t wtcdb_test_index_entry_data1[ 40 ] = {
	0x94, 0x53, 0xb1, 0x8f, 0xf9, 0x50, 0x45, 0x5c, 0x00, 0x4a, 0x6e, 0x27, 0x50, 0x63, 0xc5, 0x01,
	0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x95, 0x9c, 0x12, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

uint8_t wtcdb_test_index_entry_data2[ 32 ] = {
	0x2b, 0x0d, 0x06, 0xc0, 0x7b, 0x75, 0x1e, 0xa1, 0x02, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x17, 0x80, 0x67, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

#if defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT )

/* Tests the libwtcdb_index_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_index_entry_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	libwtcdb_index_entry_t *index_entry = NULL;
	int result                        = 0;

#if defined( HAVE_WTCDB_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = libwtcdb_index_entry_initialize(
	          &index_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "index_entry",
	 index_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_index_entry_free(
	          &index_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "index_entry",
	 index_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwtcdb_index_entry_initialize(
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

	index_entry = (libwtcdb_index_entry_t *) 0x12345678UL;

	result = libwtcdb_index_entry_initialize(
	          &index_entry,
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

	index_entry = NULL;

#if defined( HAVE_WTCDB_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwtcdb_index_entry_initialize with malloc failing
		 */
		wtcdb_test_malloc_attempts_before_fail = test_number;

		result = libwtcdb_index_entry_initialize(
		          &index_entry,
		          &error );

		if( wtcdb_test_malloc_attempts_before_fail != -1 )
		{
			wtcdb_test_malloc_attempts_before_fail = -1;

			if( index_entry != NULL )
			{
				libwtcdb_index_entry_free(
				 &index_entry,
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
			 "index_entry",
			 index_entry );

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
		/* Test libwtcdb_index_entry_initialize with memset failing
		 */
		wtcdb_test_memset_attempts_before_fail = test_number;

		result = libwtcdb_index_entry_initialize(
		          &index_entry,
		          &error );

		if( wtcdb_test_memset_attempts_before_fail != -1 )
		{
			wtcdb_test_memset_attempts_before_fail = -1;

			if( index_entry != NULL )
			{
				libwtcdb_index_entry_free(
				 &index_entry,
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
			 "index_entry",
			 index_entry );

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
	if( index_entry != NULL )
	{
		libwtcdb_index_entry_free(
		 &index_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwtcdb_index_entry_free function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_index_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwtcdb_index_entry_free(
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

/* Tests the libwtcdb_index_entry_read_data function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_index_entry_read_data(
     void )
{
	libcerror_error_t *error            = NULL;
	libwtcdb_index_entry_t *index_entry = NULL;
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

	result = libwtcdb_index_entry_initialize(
	          &index_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "index_entry",
	 index_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	io_handle->file_type      = LIBWTCDB_FILE_TYPE_INDEX;
	io_handle->format_version = 20;

	result = libwtcdb_index_entry_read_data(
	          index_entry,
	          io_handle,
	          wtcdb_test_index_entry_data1,
	          40,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->file_type      = LIBWTCDB_FILE_TYPE_INDEX;
	io_handle->format_version = 21;

	result = libwtcdb_index_entry_read_data(
	          index_entry,
	          io_handle,
	          wtcdb_test_index_entry_data1,
	          32,
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
	result = libwtcdb_index_entry_read_data(
	          NULL,
	          io_handle,
	          wtcdb_test_index_entry_data1,
	          40,
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

	result = libwtcdb_index_entry_read_data(
	          index_entry,
	          NULL,
	          wtcdb_test_index_entry_data1,
	          40,
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
	io_handle->format_version = 20;

	result = libwtcdb_index_entry_read_data(
	          index_entry,
	          io_handle,
	          wtcdb_test_index_entry_data1,
	          40,
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
	io_handle->format_version = 0;

	result = libwtcdb_index_entry_read_data(
	          index_entry,
	          io_handle,
	          wtcdb_test_index_entry_data1,
	          40,
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

	result = libwtcdb_index_entry_read_data(
	          index_entry,
	          io_handle,
	          NULL,
	          40,
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

	result = libwtcdb_index_entry_read_data(
	          index_entry,
	          io_handle,
	          wtcdb_test_index_entry_data1,
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

	result = libwtcdb_index_entry_read_data(
	          index_entry,
	          io_handle,
	          wtcdb_test_index_entry_data1,
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
	result = libwtcdb_index_entry_free(
	          &index_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "index_entry",
	 index_entry );

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
	if( index_entry != NULL )
	{
		libwtcdb_index_entry_free(
		 &index_entry,
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

/* Tests the libwtcdb_index_entry_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_index_entry_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle    = NULL;
	libcerror_error_t *error            = NULL;
	libwtcdb_index_entry_t *index_entry = NULL;
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

	result = libwtcdb_index_entry_initialize(
	          &index_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "index_entry",
	 index_entry );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = wtcdb_test_open_file_io_handle(
	          &file_io_handle,
	          wtcdb_test_index_entry_data1,
	          40,
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

	/* Test regular cases
	 */
	io_handle->file_type      = LIBWTCDB_FILE_TYPE_INDEX;
	io_handle->format_version = 20;

	result = libwtcdb_index_entry_read_file_io_handle(
	          index_entry,
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
	result = libwtcdb_index_entry_read_file_io_handle(
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

	result = libwtcdb_index_entry_read_file_io_handle(
	          index_entry,
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

	io_handle->file_type      = LIBWTCDB_FILE_TYPE_CACHE;
	io_handle->format_version = 20;

	result = libwtcdb_index_entry_read_file_io_handle(
	          index_entry,
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

	io_handle->file_type      = LIBWTCDB_FILE_TYPE_INDEX;
	io_handle->format_version = 0;

	result = libwtcdb_index_entry_read_file_io_handle(
	          index_entry,
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

	result = libwtcdb_index_entry_read_file_io_handle(
	          index_entry,
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

	/* Clean up file IO handle
	 */
	result = wtcdb_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libwtcdb_index_entry_free(
	          &index_entry,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "index_entry",
	 index_entry );

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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( index_entry != NULL )
	{
		libwtcdb_index_entry_free(
		 &index_entry,
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
	 "libwtcdb_index_entry_initialize",
	 wtcdb_test_index_entry_initialize );

	WTCDB_TEST_RUN(
	 "libwtcdb_index_entry_free",
	 wtcdb_test_index_entry_free );

	WTCDB_TEST_RUN(
	 "libwtcdb_index_entry_read_data",
	 wtcdb_test_index_entry_read_data );

	WTCDB_TEST_RUN(
	 "libwtcdb_index_entry_read_file_io_handle",
	 wtcdb_test_index_entry_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

