/*
 * Library file type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "wtcdb_test_functions.h"
#include "wtcdb_test_getopt.h"
#include "wtcdb_test_libbfio.h"
#include "wtcdb_test_libcerror.h"
#include "wtcdb_test_libwtcdb.h"
#include "wtcdb_test_macros.h"
#include "wtcdb_test_memory.h"
#include "wtcdb_test_unused.h"

#include "../libwtcdb/libwtcdb_file.h"

#if !defined( LIBWTCDB_HAVE_BFIO )

LIBWTCDB_EXTERN \
int libwtcdb_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBWTCDB_EXTERN \
int libwtcdb_file_open_file_io_handle(
     libwtcdb_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libwtcdb_error_t **error );

#endif /* !defined( LIBWTCDB_HAVE_BFIO ) */

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make wtcdb_test_file generate verbose output
#define WTCDB_TEST_FILE_VERBOSE
 */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int wtcdb_test_file_open_source(
     libwtcdb_file_t **file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "wtcdb_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libwtcdb_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	result = libwtcdb_file_open_file_io_handle(
	          *file,
	          file_io_handle,
	          LIBWTCDB_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libwtcdb_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int wtcdb_test_file_close_source(
     libwtcdb_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "wtcdb_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libwtcdb_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libwtcdb_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libwtcdb_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libwtcdb_file_t *file           = NULL;
	int result                      = 0;

#if defined( HAVE_WTCDB_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libwtcdb_file_initialize(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_file_free(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwtcdb_file_initialize(
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

	file = (libwtcdb_file_t *) 0x12345678UL;

	result = libwtcdb_file_initialize(
	          &file,
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

	file = NULL;

#if defined( HAVE_WTCDB_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwtcdb_file_initialize with malloc failing
		 */
		wtcdb_test_malloc_attempts_before_fail = test_number;

		result = libwtcdb_file_initialize(
		          &file,
		          &error );

		if( wtcdb_test_malloc_attempts_before_fail != -1 )
		{
			wtcdb_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libwtcdb_file_free(
				 &file,
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
			 "file",
			 file );

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
		/* Test libwtcdb_file_initialize with memset failing
		 */
		wtcdb_test_memset_attempts_before_fail = test_number;

		result = libwtcdb_file_initialize(
		          &file,
		          &error );

		if( wtcdb_test_memset_attempts_before_fail != -1 )
		{
			wtcdb_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libwtcdb_file_free(
				 &file,
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
			 "file",
			 file );

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
	if( file != NULL )
	{
		libwtcdb_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwtcdb_file_free function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwtcdb_file_free(
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

/* Tests the libwtcdb_file_open function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libwtcdb_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = wtcdb_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_file_initialize(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libwtcdb_file_open(
	          file,
	          narrow_source,
	          LIBWTCDB_OPEN_READ,
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
	result = libwtcdb_file_open(
	          NULL,
	          narrow_source,
	          LIBWTCDB_OPEN_READ,
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

	result = libwtcdb_file_open(
	          file,
	          NULL,
	          LIBWTCDB_OPEN_READ,
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

	result = libwtcdb_file_open(
	          file,
	          narrow_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libwtcdb_file_open(
	          file,
	          narrow_source,
	          LIBWTCDB_OPEN_READ,
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
	result = libwtcdb_file_free(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libwtcdb_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libwtcdb_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libwtcdb_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = wtcdb_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_file_initialize(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libwtcdb_file_open_wide(
	          file,
	          wide_source,
	          LIBWTCDB_OPEN_READ,
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
	result = libwtcdb_file_open_wide(
	          NULL,
	          wide_source,
	          LIBWTCDB_OPEN_READ,
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

	result = libwtcdb_file_open_wide(
	          file,
	          NULL,
	          LIBWTCDB_OPEN_READ,
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

	result = libwtcdb_file_open_wide(
	          file,
	          wide_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libwtcdb_file_open_wide(
	          file,
	          wide_source,
	          LIBWTCDB_OPEN_READ,
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
	result = libwtcdb_file_free(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libwtcdb_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libwtcdb_file_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libwtcdb_file_t *file            = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
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

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        WTCDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libwtcdb_file_initialize(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libwtcdb_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBWTCDB_OPEN_READ,
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
	result = libwtcdb_file_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBWTCDB_OPEN_READ,
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

	result = libwtcdb_file_open_file_io_handle(
	          file,
	          NULL,
	          LIBWTCDB_OPEN_READ,
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

	result = libwtcdb_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          -1,
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

	/* Test open when already opened
	 */
	result = libwtcdb_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBWTCDB_OPEN_READ,
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
	result = libwtcdb_file_free(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libwtcdb_file_free(
		 &file,
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

/* Tests the libwtcdb_file_close function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwtcdb_file_close(
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

/* Tests the libwtcdb_file_open and libwtcdb_file_close functions
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libwtcdb_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libwtcdb_file_initialize(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwtcdb_file_open_wide(
	          file,
	          source,
	          LIBWTCDB_OPEN_READ,
	          &error );
#else
	result = libwtcdb_file_open(
	          file,
	          source,
	          LIBWTCDB_OPEN_READ,
	          &error );
#endif

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_file_close(
	          file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwtcdb_file_open_wide(
	          file,
	          source,
	          LIBWTCDB_OPEN_READ,
	          &error );
#else
	result = libwtcdb_file_open(
	          file,
	          source,
	          LIBWTCDB_OPEN_READ,
	          &error );
#endif

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwtcdb_file_close(
	          file,
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
	result = libwtcdb_file_free(
	          &file,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libwtcdb_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwtcdb_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_signal_abort(
     libwtcdb_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwtcdb_file_signal_abort(
	          file,
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
	result = libwtcdb_file_signal_abort(
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

/* Tests the libwtcdb_file_get_type function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_get_type(
     libwtcdb_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint8_t type             = 0;
	int result               = 0;
	int type_is_set          = 0;

	/* Test regular cases
	 */
	result = libwtcdb_file_get_type(
	          file,
	          &type,
	          &error );

	WTCDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	type_is_set = result;

	/* Test error cases
	 */
	result = libwtcdb_file_get_type(
	          NULL,
	          &type,
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

	if( type_is_set != 0 )
	{
		result = libwtcdb_file_get_type(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwtcdb_file_get_number_of_items function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_get_number_of_items(
     libwtcdb_file_t *file )
{
	libcerror_error_t *error   = NULL;
	int number_of_items        = 0;
	int number_of_items_is_set = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	result = libwtcdb_file_get_number_of_items(
	          file,
	          &number_of_items,
	          &error );

	WTCDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_items_is_set = result;

	/* Test error cases
	 */
	result = libwtcdb_file_get_number_of_items(
	          NULL,
	          &number_of_items,
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

	if( number_of_items_is_set != 0 )
	{
		result = libwtcdb_file_get_number_of_items(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwtcdb_file_get_item function
 * Returns 1 if successful or 0 if not
 */
int wtcdb_test_file_get_item(
     libwtcdb_file_t *file )
{
	libcerror_error_t *error = NULL;
	libwtcdb_item_t *item    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwtcdb_file_get_item(
	          file,
	          0,
	          &item,
	          &error );

	WTCDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "item",
	 item );

	result = libwtcdb_item_free(
	          &item,
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
	result = libwtcdb_file_get_item(
	          NULL,
	          0,
	          &item,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "item",
	 item );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwtcdb_file_get_item(
	          file,
	          -1,
	          &item,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "item",
	 item );

	WTCDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwtcdb_file_get_item(
	          file,
	          0,
	          NULL,
	          &error );

	WTCDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WTCDB_TEST_ASSERT_IS_NULL(
	 "item",
	 item );

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

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libwtcdb_file_t *file            = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = wtcdb_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( WTCDB_TEST_FILE_VERBOSE )
	libwtcdb_notify_set_verbose(
	 1 );
	libwtcdb_notify_set_stream(
	 stderr,
	 NULL );
#endif

	WTCDB_TEST_RUN(
	 "libwtcdb_file_initialize",
	 wtcdb_test_file_initialize );

	WTCDB_TEST_RUN(
	 "libwtcdb_file_free",
	 wtcdb_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
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

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		WTCDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        WTCDB_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libwtcdb_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		WTCDB_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		WTCDB_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		WTCDB_TEST_RUN_WITH_ARGS(
		 "libwtcdb_file_open",
		 wtcdb_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		WTCDB_TEST_RUN_WITH_ARGS(
		 "libwtcdb_file_open_wide",
		 wtcdb_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		WTCDB_TEST_RUN_WITH_ARGS(
		 "libwtcdb_file_open_file_io_handle",
		 wtcdb_test_file_open_file_io_handle,
		 source );

		WTCDB_TEST_RUN(
		 "libwtcdb_file_close",
		 wtcdb_test_file_close );

		WTCDB_TEST_RUN_WITH_ARGS(
		 "libwtcdb_file_open_close",
		 wtcdb_test_file_open_close,
		 source );

		/* Initialize file for tests
		 */
		result = wtcdb_test_file_open_source(
		          &file,
		          file_io_handle,
		          &error );

		WTCDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		WTCDB_TEST_ASSERT_IS_NOT_NULL(
		 "file",
		 file );

		WTCDB_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		WTCDB_TEST_RUN_WITH_ARGS(
		 "libwtcdb_file_signal_abort",
		 wtcdb_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT )

		/* TODO: add tests for libwtcdb_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBWTCDB_DLL_IMPORT ) */

		WTCDB_TEST_RUN_WITH_ARGS(
		 "libwtcdb_file_get_type",
		 wtcdb_test_file_get_type,
		 file );

		WTCDB_TEST_RUN_WITH_ARGS(
		 "libwtcdb_file_get_number_of_items",
		 wtcdb_test_file_get_number_of_items,
		 file );

#if defined( TODO )

		WTCDB_TEST_RUN_WITH_ARGS(
		 "libwtcdb_file_get_item",
		 wtcdb_test_file_get_item,
		 file );

#endif /* defined( TODO ) */

		/* Clean up
		 */
		result = wtcdb_test_file_close_source(
		          &file,
		          &error );

		WTCDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		WTCDB_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

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
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libwtcdb_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

