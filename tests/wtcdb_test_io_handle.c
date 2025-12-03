/*
 * Library io_handle type test program
 *
 * Copyright (C) 2010-2025, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "wtcdb_test_libcerror.h"
#include "wtcdb_test_libwtcdb.h"
#include "wtcdb_test_macros.h"
#include "wtcdb_test_memory.h"
#include "wtcdb_test_unused.h"

#include "../libwtcdb/libwtcdb_io_handle.h"

#if defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT )

/* Tests the libwtcdb_io_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_io_handle_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libwtcdb_io_handle_t *io_handle = NULL;
	int result                      = 0;

#if defined( HAVE_WTCDB_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
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

	/* Test error cases
	 */
	result = libwtcdb_io_handle_initialize(
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

	io_handle = (libwtcdb_io_handle_t *) 0x12345678UL;

	result = libwtcdb_io_handle_initialize(
	          &io_handle,
	          &error );

	io_handle = NULL;

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_WTCDB_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwtcdb_io_handle_initialize with malloc failing
		 */
		wtcdb_test_malloc_attempts_before_fail = test_number;

		result = libwtcdb_io_handle_initialize(
		          &io_handle,
		          &error );

		if( wtcdb_test_malloc_attempts_before_fail != -1 )
		{
			wtcdb_test_malloc_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libwtcdb_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
		/* Test libwtcdb_io_handle_initialize with memset failing
		 */
		wtcdb_test_memset_attempts_before_fail = test_number;

		result = libwtcdb_io_handle_initialize(
		          &io_handle,
		          &error );

		if( wtcdb_test_memset_attempts_before_fail != -1 )
		{
			wtcdb_test_memset_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libwtcdb_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
	if( io_handle != NULL )
	{
		libwtcdb_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwtcdb_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwtcdb_io_handle_free(
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

/* Tests the libwtcdb_io_handle_clear function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_io_handle_clear(
     void )
{
	libcerror_error_t *error        = NULL;
	libwtcdb_io_handle_t *io_handle = NULL;
	int result                      = 0;

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

	/* Test regular cases
	 */
	result = libwtcdb_io_handle_clear(
	          io_handle,
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
	result = libwtcdb_io_handle_clear(
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

#if defined( HAVE_WTCDB_TEST_MEMORY )

	/* Test libwtcdb_io_handle_clear with memset failing
	 */
	wtcdb_test_memset_attempts_before_fail = 0;

	result = libwtcdb_io_handle_clear(
	          io_handle,
	          &error );

	if( wtcdb_test_memset_attempts_before_fail != -1 )
	{
		wtcdb_test_memset_attempts_before_fail = -1;
	}
	else
	{
		WTCDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		WTCDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_WTCDB_TEST_MEMORY ) */

	/* Clean up
	 */
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
	 "libwtcdb_io_handle_initialize",
	 wtcdb_test_io_handle_initialize );

	WTCDB_TEST_RUN(
	 "libwtcdb_io_handle_free",
	 wtcdb_test_io_handle_free );

	WTCDB_TEST_RUN(
	 "libwtcdb_io_handle_clear",
	 wtcdb_test_io_handle_clear );

#endif /* defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

