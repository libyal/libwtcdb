/*
 * Library file_header type test program
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

#include "../libwtcdb/libwtcdb_file_header.h"

uint8_t wtcdb_test_file_header_data1[ 24 ] = {
	0x43, 0x4d, 0x4d, 0x4d, 0x14, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
	0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t wtcdb_test_file_header_data2[ 24 ] = {
	0x49, 0x4d, 0x4d, 0x4d, 0x14, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00,
	0xca, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT )

/* Tests the libwtcdb_file_header_initialize function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_header_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	libwtcdb_file_header_t *file_header = NULL;
	int result                        = 0;

#if defined( HAVE_WTCDB_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = libwtcdb_file_header_initialize(
	          &file_header,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_file_header_free(
	          &file_header,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwtcdb_file_header_initialize(
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

	file_header = (libwtcdb_file_header_t *) 0x12345678UL;

	result = libwtcdb_file_header_initialize(
	          &file_header,
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

	file_header = NULL;

#if defined( HAVE_WTCDB_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwtcdb_file_header_initialize with malloc failing
		 */
		wtcdb_test_malloc_attempts_before_fail = test_number;

		result = libwtcdb_file_header_initialize(
		          &file_header,
		          &error );

		if( wtcdb_test_malloc_attempts_before_fail != -1 )
		{
			wtcdb_test_malloc_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				libwtcdb_file_header_free(
				 &file_header,
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
			 "file_header",
			 file_header );

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
		/* Test libwtcdb_file_header_initialize with memset failing
		 */
		wtcdb_test_memset_attempts_before_fail = test_number;

		result = libwtcdb_file_header_initialize(
		          &file_header,
		          &error );

		if( wtcdb_test_memset_attempts_before_fail != -1 )
		{
			wtcdb_test_memset_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				libwtcdb_file_header_free(
				 &file_header,
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
			 "file_header",
			 file_header );

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
	if( file_header != NULL )
	{
		libwtcdb_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwtcdb_file_header_free function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_header_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwtcdb_file_header_free(
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

/* Tests the libwtcdb_file_header_read_data function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_header_read_data(
     void )
{
	libcerror_error_t *error            = NULL;
	libwtcdb_file_header_t *file_header = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libwtcdb_file_header_initialize(
	          &file_header,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwtcdb_file_header_read_data(
	          file_header,
	          wtcdb_test_file_header_data1,
	          24,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_file_header_read_data(
	          file_header,
	          wtcdb_test_file_header_data2,
	          24,
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
	result = libwtcdb_file_header_read_data(
	          NULL,
	          wtcdb_test_file_header_data1,
	          24,
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

	result = libwtcdb_file_header_read_data(
	          file_header,
	          NULL,
	          24,
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

	result = libwtcdb_file_header_read_data(
	          file_header,
	          wtcdb_test_file_header_data1,
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

	result = libwtcdb_file_header_read_data(
	          file_header,
	          wtcdb_test_file_header_data1,
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
	result = libwtcdb_file_header_free(
	          &file_header,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

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
	if( file_header != NULL )
	{
		libwtcdb_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwtcdb_file_header_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_header_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle    = NULL;
	libcerror_error_t *error            = NULL;
	libwtcdb_file_header_t *file_header = NULL;
	int result                          = 0;

	/* Initialize test
	 */
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
	          wtcdb_test_file_header_data1,
	          24,
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

	result = libwtcdb_file_header_initialize(
	          &file_header,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwtcdb_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
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
	result = libwtcdb_file_header_read_file_io_handle(
	          NULL,
	          file_io_handle,
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

	result = libwtcdb_file_header_read_file_io_handle(
	          file_header,
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

	/* Clean up
	 */
	result = libwtcdb_file_header_free(
	          &file_header,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

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
	if( file_header != NULL )
	{
		libwtcdb_file_header_free(
		 &file_header,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
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
	 "libwtcdb_file_header_initialize",
	 wtcdb_test_file_header_initialize );

	WTCDB_TEST_RUN(
	 "libwtcdb_file_header_free",
	 wtcdb_test_file_header_free );

	WTCDB_TEST_RUN(
	 "libwtcdb_file_header_read_data",
	 wtcdb_test_file_header_read_data );

	WTCDB_TEST_RUN(
	 "libwtcdb_file_header_read_file_io_handle",
	 wtcdb_test_file_header_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

