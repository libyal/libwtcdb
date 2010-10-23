/*
 * Extracts items from a Nickfile (WTCDB)
 *
 * Copyright (c) 2009-2010, Joachim Metz <jbmetz@users.sourceforge.net>
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
#include <memory.h>
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#include <stdio.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

/* If libtool DLL support is enabled set LIBWTCDB_DLL_IMPORT
 * before including libwtcdb.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBWTCDB_DLL_IMPORT
#endif

#include <libwtcdb.h>

#include <libsystem.h>

#include "export_handle.h"
#include "log_handle.h"
#include "wtcdboutput.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use wtcdbexport to export items stored in a Nickfile (WTCDB).\n\n" );

	fprintf( stream, "Usage: wtcdbexport [ -l logfile ] [ -t target ] [ -hvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file\n\n" );

	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-l:     logs information about the exported items\n" );
	fprintf( stream, "\t-t:     specify the target directory to export to\n"
	                 "\t        (default is the source filename followed by .export)\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	export_handle_t *export_handle                    = NULL;
	liberror_error_t *error                           = NULL;
	libwtcdb_file_t *wtcdb_file                       = NULL;
	log_handle_t *log_handle                          = NULL;
	libcstring_system_character_t *log_filename       = NULL;
	libcstring_system_character_t *option_target_path = NULL;
	libcstring_system_character_t *path_separator     = NULL;
	libcstring_system_character_t *source             = NULL;
	libcstring_system_character_t *target_path        = NULL;
	char *program                                     = "wtcdbexport";
	size_t source_length                              = 0;
	size_t target_path_length                         = 0;
	libcstring_system_integer_t option                = 0;
	int result                                        = 0;
	int verbose                                       = 0;

	libsystem_notify_set_stream(
	 stderr,
	 NULL );
	libsystem_notify_set_verbose(
	 1 );

        if( libsystem_initialize(
             "wtcdbtools",
             &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize system values.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	wtcdboutput_version_fprint(
	 stdout,
	 program );

	while( ( option = libsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "hl:t:vV" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM "\n",
				 argv[ optind ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (libcstring_system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (libcstring_system_integer_t) 'l':
				log_filename = optarg;

				break;

			case (libcstring_system_integer_t) 't':
				option_target_path = optarg;

				break;

			case (libcstring_system_integer_t) 'v':
				verbose = 1;

				break;

			case (libcstring_system_integer_t) 'V':
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

	if( option_target_path != NULL )
	{
		target_path_length = libcstring_system_string_length(
		                      option_target_path );

		if( target_path_length > 0 )
		{
			target_path = (libcstring_system_character_t *) memory_allocate(
			                                                 sizeof( libcstring_system_character_t ) * ( target_path_length + 1 ) );

			if( target_path == NULL )
			{
				fprintf(
				 stderr,
				 "Unable to create target path.\n" );

				return( EXIT_FAILURE );
			}
			else if( libcstring_system_string_copy(
			          target_path,
			          option_target_path,
			          target_path_length ) == NULL )
			{
				fprintf(
				 stderr,
				 "Unable to set target path.\n" );

				memory_free(
				 target_path );

				return( EXIT_FAILURE );
			}
			target_path[ target_path_length ] = 0;
		}
	}
	else
	{
		source_length = libcstring_system_string_length(
		                 source );

		path_separator = libcstring_system_string_search_character_reverse(
		                  source,
		                  (libcstring_system_character_t) LIBSYSTEM_PATH_SEPARATOR,
		                  source_length );

		if( path_separator == NULL )
		{
			path_separator = source;
		}
		else
		{
			path_separator++;
		}
		target_path_length = 7 + libcstring_system_string_length(
		                          path_separator );

		target_path = (libcstring_system_character_t *) memory_allocate(
		                                                 sizeof( libcstring_system_character_t ) * ( target_path_length + 1 ) );

		if( target_path == NULL )
		{
			fprintf(
			 stderr,
			 "Unable to create target path.\n" );

			return( EXIT_FAILURE );
		}
		if( libcstring_system_string_sprintf(
		     target_path,
		     target_path_length + 1,
		     _LIBCSTRING_SYSTEM_STRING( "%" ) _LIBCSTRING_SYSTEM_STRING( PRIs_LIBCSTRING_SYSTEM ) _LIBCSTRING_SYSTEM_STRING( ".export" ),
		     path_separator ) == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to set target path.\n" );

			memory_free(
			 target_path );

			return( EXIT_FAILURE );
		}
	}
	result = libsystem_file_exists(
	          target_path,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to determine if %" PRIs_LIBCSTRING_SYSTEM " exists.\n",
		 target_path );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );
	}
	else if( result == 1 )
	{
		fprintf(
		 stderr,
		 "%" PRIs_LIBCSTRING_SYSTEM " already exists.\n",
		 target_path );
	}
	if( result != 0 )
	{
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	libsystem_notify_set_verbose(
	 verbose );
	libwtcdb_notify_set_stream(
	 stderr,
	 NULL );
	libwtcdb_notify_set_verbose(
	 verbose );

	if( log_handle_initialize(
	     &log_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize log handle.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	if( export_handle_initialize(
	     &export_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize export handle.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		log_handle_free(
		 &log_handle,
		 NULL );
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	if( libwtcdb_file_initialize(
	     &wtcdb_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize WTCDB file.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		export_handle_free(
		 &export_handle,
		 NULL );
		log_handle_free(
		 &log_handle,
		 NULL );
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	if( log_handle_open(
	     log_handle,
	     log_filename,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open log file: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 log_filename );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		libwtcdb_file_free(
		 &wtcdb_file,
		 NULL );
		export_handle_free(
		 &export_handle,
		 NULL );
		log_handle_free(
		 &log_handle,
		 NULL );
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	fprintf(
	 stdout,
	 "Opening file.\n" );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "Error opening file: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 source );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		libwtcdb_file_free(
		 &wtcdb_file,
		 NULL );
		export_handle_free(
		 &export_handle,
		 NULL );
		log_handle_free(
		 &log_handle,
		 NULL );
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	fprintf(
	 stdout,
	 "Exporting aliases.\n" );

	result = export_handle_export_file(
	          export_handle,
	          wtcdb_file,
	          target_path,
	          target_path_length + 1,
	          log_handle,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to export file.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		libwtcdb_file_close(
		 wtcdb_file,
		 NULL );
		libwtcdb_file_free(
		 &wtcdb_file,
		 NULL );
		export_handle_free(
		 &export_handle,
		 NULL );
		log_handle_free(
		 &log_handle,
		 NULL );
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	memory_free(
	 target_path );

	if( libwtcdb_file_close(
	     wtcdb_file,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Error closing file: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 source );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		libwtcdb_file_free(
		 &wtcdb_file,
		 NULL );
		export_handle_free(
		 &export_handle,
		 NULL );
		log_handle_free(
		 &log_handle,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( libwtcdb_file_free(
	     &wtcdb_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free WTCDB file.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		export_handle_free(
		 &export_handle,
		 NULL );
		log_handle_free(
		 &log_handle,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( export_handle_free(
	     &export_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free export handle.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		log_handle_free(
		 &log_handle,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( log_handle_close(
	     log_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close log file: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 log_filename );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		log_handle_free(
		 &log_handle,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( log_handle_free(
	     &log_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free log handle.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "No aliases to export.\n" );
	}
	else
	{
		fprintf(
		 stdout,
		 "Export completed.\n" );
	}
	return( EXIT_SUCCESS );
}

