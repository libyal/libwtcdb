/*
 * Shows information obtained from a Windows Explorer thumbnail cache database file
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <system_string.h>
#include <types.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "wtcdbtools_getopt.h"
#include "wtcdbtools_libcerror.h"
#include "wtcdbtools_libclocale.h"
#include "wtcdbtools_libcnotify.h"
#include "wtcdbtools_libwtcdb.h"
#include "wtcdbtools_output.h"
#include "wtcdbtools_signal.h"
#include "wtcdbtools_unused.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use wtcdbinfo to determine information about a Windows Explorer\n"
	                 "thumbnail cache database (thumbcache.db) file.\n\n" );

	fprintf( stream, "Usage: wtcdbinfo [ -hvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file\n\n" );

	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Prints file information
 * Returns 1 if successful or -1 on error
 */
int wtcdbinfo_file_info_fprint(
     FILE *stream,
     libwtcdb_file_t *file,
     libcerror_error_t **error )
{
	static char *function = "wtcdbinfo_file_info_fprint";
	uint8_t file_type     = 0;
	int number_of_items   = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
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
	if( libwtcdb_file_get_type(
	     file,
	     &file_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file type.",
		 function );

		return( -1 );
	}
	if( libwtcdb_file_get_number_of_items(
	     file,
	     &number_of_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of items.",
		 function );

		return( -1 );
	}
	fprintf(
	 stream,
	 "Windows Explorer thumbnail cache database information:\n" );

	fprintf(
	 stream,
	 "\tFile type:\t\t" );

	if( file_type == LIBWTCDB_FILE_TYPE_CACHE )
	{
		fprintf(
		 stream,
		 "Cache file" );
	}
	else if( file_type == LIBWTCDB_FILE_TYPE_INDEX )
	{
		fprintf(
		 stream,
		 "Index file" );
	}
	fprintf(
	 stream,
	 "\n" );

	fprintf(
	 stream,
	 "\tNumber of items:\t%d\n",
	 number_of_items );

	fprintf(
	 stream,
	 "\n" );

	return( 1 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error    = NULL;
	libwtcdb_file_t *wtcdb_file = NULL;
	system_character_t *source  = NULL;
	char *program               = "wtcdbinfo";
	system_integer_t option     = 0;
	int verbose                 = 0;

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
	     "wtcdbtools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
	if( wtcdbtools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	wtcdboutput_version_fprint(
	 stdout,
	 program );

	while( ( option = wtcdbtools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "hvV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				wtcdboutput_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libwtcdb_notify_set_stream(
	 stderr,
	 NULL );
	libwtcdb_notify_set_verbose(
	 verbose );

	if( libwtcdb_file_initialize(
	     &wtcdb_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize libwtcdb file.\n" );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libwtcdb_file_open_wide(
	     wtcdb_file,
	     source,
	     LIBWTCDB_OPEN_READ,
	     &error ) != 1 )
#else
	if( libwtcdb_file_open(
	     wtcdb_file,
	     source,
	     LIBWTCDB_OPEN_READ,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Error opening file: %" PRIs_SYSTEM ".\n",
		 source );

		goto on_error;
	}
	if( wtcdbinfo_file_info_fprint(
	     stdout,
	     wtcdb_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print file information.\n" );

		goto on_error;
	}
	if( libwtcdb_file_close(
	     wtcdb_file,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Error closing file: %" PRIs_SYSTEM ".\n",
		 argv[ optind ] );

		goto on_error;
	}
	if( libwtcdb_file_free(
	     &wtcdb_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free libwtcdb file.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( wtcdb_file != NULL )
	{
		libwtcdb_file_close(
		 wtcdb_file,
		 NULL );
		libwtcdb_file_free(
		 &wtcdb_file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

