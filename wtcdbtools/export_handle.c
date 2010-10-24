/* 
 * Export handle
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

#include <libsystem.h>

#include "export_handle.h"
#include "log_handle.h"

/* Initializes the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_initialize(
     export_handle_t **export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_initialize";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle == NULL )
	{
		*export_handle = (export_handle_t *) memory_allocate(
		                                      sizeof( export_handle_t ) );

		if( *export_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create export handle.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *export_handle,
		     0,
		     sizeof( export_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear export handle.",
			 function );

			memory_free(
			 *export_handle );

			*export_handle = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees the export handle and its elements
 * Returns 1 if successful or -1 on error
 */
int export_handle_free(
     export_handle_t **export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_free";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( 1 );
}

/* Create a directory
 * Returns 1 if successful or -1 on error
 */
int export_handle_make_directory(
     export_handle_t *export_handle,
     libcstring_system_character_t *directory_name,
     log_handle_t *log_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_make_directory";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( directory_name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory name.",
		 function );

		return( -1 );
	}
	if( libsystem_directory_make(
	     directory_name ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to make directory: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 directory_name );

		return( -1 );
	}
	log_handle_printf(
	 log_handle,
	 "Created directory: %" PRIs_LIBCSTRING_SYSTEM ".\n",
	 directory_name );

	return( 1 );
}

/* Sanitizes the filename
 * Returns 1 if successful or -1 on error
 */
int export_handle_sanitize_filename(
     export_handle_t *export_handle,
     libcstring_system_character_t *filename,
     size_t filename_size,
     liberror_error_t **error )
{
	static char *function = "export_handle_sanitize_filename";
	size_t iterator       = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( filename_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid filename size value exceeds maximum.",
		 function );

		return( -1 );
	}
	for( iterator = 0; iterator < filename_size; iterator++ )
	{
		if( ( ( filename[ iterator ] >= 0x01 )
		  && ( filename[ iterator ] <= 0x1f ) )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '!' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '$' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '%' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '&' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '*' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '+' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '/' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) ':' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) ';' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '<' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '>' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '?' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '@' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '\\' )
		 || ( filename[ iterator ] == (libcstring_system_character_t) '~' )
		 || ( filename[ iterator ] == 0x7e ) )
		{
			filename[ iterator ] = (libcstring_system_character_t) '_';
		}
	}
	return( 1 );
}

/* Creates the target path
 * Returns 1 if successful or -1 on error
 */
int export_handle_create_target_path(
     export_handle_t *export_handle,
     libcstring_system_character_t *export_path,
     size_t export_path_size,
     uint8_t *utf8_filename,
     size_t utf8_filename_size,
     libcstring_system_character_t **target_path,
     size_t *target_path_size,
     liberror_error_t **error )
{
	static char *function = "export_handle_create_target_path";
	size_t filename_size  = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
		 function );

		return( -1 );
	}
	if( utf8_filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 filename.",
		 function );

		return( -1 );
	}
	if( utf8_filename_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 filename size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( target_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		return( -1 );
	}
	if( *target_path != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid target path already set.",
		 function );

		return( -1 );
	}
	if( target_path_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path size.",
		 function );

		return( -1 );
	}
	/* Make sure to check the UTF-8 filename length
	 * the conversion routines are very strict about the string size
	 */
	utf8_filename_size = 1 + libcstring_narrow_string_length(
	                          (char *) utf8_filename );

	if( libsystem_string_size_from_utf8_string(
	     utf8_filename,
	     utf8_filename_size,
	     &filename_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine UTF-8 filename size.",
		 function );

		return( -1 );
	}
	/* Include space for the separator and the end of string character
	 */
	*target_path_size = export_path_size + filename_size;

	*target_path = (libcstring_system_character_t *) memory_allocate(
	                                                  sizeof( libcstring_system_character_t ) * *target_path_size );

	if( *target_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create target path.",
		 function );

		*target_path_size = 0;

		return( -1 );
	}
	if( libcstring_system_string_copy(
	     *target_path,
	     export_path,
	     export_path_size ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set export path in target path.",
		 function );

		memory_free(
		 target_path );

		*target_path      = NULL;
		*target_path_size = 0;

		return( -1 );
	}
	( *target_path )[ export_path_size - 1 ] = (libcstring_system_character_t) LIBSYSTEM_PATH_SEPARATOR;

	if( libsystem_string_copy_from_utf8_string(
	     &( ( *target_path )[ export_path_size ] ),
	     filename_size,
	     utf8_filename,
	     utf8_filename_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set filename in target path.",
		 function );

		memory_free(
		 target_path );

		*target_path      = NULL;
		*target_path_size = 0;

		return( -1 );
	}
	if( export_handle_sanitize_filename(
	     export_handle,
	     &( ( *target_path )[ export_path_size ] ),
	     filename_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable sanitize filename in target path.",
		 function );

		memory_free(
		 target_path );

		*target_path      = NULL;
		*target_path_size = 0;

		return( -1 );
	}
	return( 1 );
}

/* Prints the data on the stream
 * Returns the number of printed characters if successful or -1 on error
 */
int export_handle_print_data(
     export_handle_t *export_handle,
     FILE *stream,
     const uint8_t *data,
     size_t data_size,
     liberror_error_t **error )
{
	static char *function = "export_handle_print_data";
	size_t byte_iterator  = 0;
	size_t data_iterator  = 0;
	int print_count       = 0;
	int total_print_count = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		return( 0 );
	}
	while( data_iterator < data_size )
	{
		while( byte_iterator < data_size )
		{
			if( byte_iterator % 16 == 0 )
			{
				print_count = fprintf(
					       stream,
					       "%.8" PRIzx ": ",
					       byte_iterator );

				/* TODO check return value upper range */

				if( print_count <= -1 )
				{
					return( -1 );
				}
				total_print_count += print_count;
			}
			print_count = fprintf(
				       stream,
				       "%.2" PRIx8 " ",
				       data[ byte_iterator++ ] );

			/* TODO check return value upper range */

			if( print_count <= -1 )
			{
				return( -1 );
			}
			total_print_count += print_count;

			if( byte_iterator % 16 == 0 )
			{
				break;
			}
			else if( byte_iterator % 8 == 0 )
			{
				print_count = fprintf(
					       stream,
					       " " );

				/* TODO check return value upper range */

				if( print_count <= -1 )
				{
					return( -1 );
				}
				total_print_count += print_count;
			}
		}
		while( byte_iterator % 16 != 0 )
		{
			byte_iterator++;

			print_count = fprintf(
				       stream,
				       "   " );

			/* TODO check return value upper range */

			if( print_count <= -1 )
			{
				return( -1 );
			}
			total_print_count += print_count;

			if( ( byte_iterator % 8 == 0 )
			 && ( byte_iterator % 16 != 0 ) )
			{
				print_count = fprintf(
					       stream,
					       " " );

				/* TODO check return value upper range */

				if( print_count <= -1 )
				{
					return( -1 );
				}
				total_print_count += print_count;
			}
		}
		print_count = fprintf(
			       stream,
			       "  " );

		/* TODO check return value upper range */

		if( print_count <= -1 )
		{
			return( -1 );
		}
		total_print_count += print_count;

		byte_iterator = data_iterator;

		while( byte_iterator < data_size )
		{
			if( ( data[ byte_iterator ] >= 0x20 )
			 && ( data[ byte_iterator ] <= 0x7e ) )
			{
				print_count = fprintf(
					       stream,
					       "%c",
					       (char) data[ byte_iterator ] );
			}
			else
			{
				print_count = fprintf(
					       stream,
					       "." );
			}
			/* TODO check return value upper range */

			if( print_count <= -1 )
			{
				return( -1 );
			}
			total_print_count += print_count;

			byte_iterator++;

			if( byte_iterator % 16 == 0 )
			{
				break;
			}
			else if( byte_iterator % 8 == 0 )
			{
				print_count = fprintf(
					       stream,
					       " " );

				/* TODO check return value upper range */

				if( print_count <= -1 )
				{
					return( -1 );
				}
				total_print_count += print_count;
			}
		}
		print_count = fprintf(
			       stream,
			       "\n" );

		/* TODO check return value upper range */

		if( print_count <= -1 )
		{
			return( -1 );
		}
		total_print_count += print_count;

		data_iterator = byte_iterator;
	}
	print_count = fprintf(
		       stream,
		       "\n" );

	/* TODO check return value upper range */

	if( print_count <= -1 )
	{
		return( -1 );
	}
	total_print_count += print_count;

	return( total_print_count );
}

/* Exports the alias
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_alias(
     export_handle_t *export_handle,
     libwtcdb_item_t *alias,
     int alias_index,
     int number_of_aliases,
     libcstring_system_character_t *export_path,
     size_t export_path_size,
     log_handle_t *log_handle,
     liberror_error_t **error )
{
	uint8_t alias_directory[ 11 ];

	libcstring_system_character_t *alias_path  = NULL;
	static char *function              = "export_handle_export_alias";
	size_t alias_directory_size        = 0;
	size_t alias_path_size             = 0;
	int print_count                    = 0;
	int result                         = 0;

#ifdef TODO
	libcstring_system_character_t *target_path = NULL;
	FILE *alias_file_stream            = NULL;
	size_t target_path_size            = 0;
#endif

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( alias == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid alias.",
		 function );

		return( -1 );
	}
	if( export_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
		 function );

		return( -1 );
	}
	fprintf(
	 stdout,
	 "Processing alias %d out of %d.\n",
	 alias_index + 1,
	 number_of_aliases );

	/* Create the alias directory
	 */
	print_count = libcstring_narrow_string_snprintf(
	               (char *) alias_directory,
	               11,
	               "Alias%05d",
	               alias_index + 1 );

	if( ( print_count < 0 )
	 || ( print_count > 11 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set alias directory.",
		 function );

		return( -1 );
	}
	alias_directory[ 10 ] = 0;
	alias_directory_size = 11;

	if( export_handle_create_target_path(
	     export_handle,
	     export_path,
	     export_path_size,
	     alias_directory,
	     alias_directory_size,
	     &alias_path,
	     &alias_path_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable create alias path.",
		 function );

		return( -1 );
	}
	if( alias_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid alias path.",
		 function );

		return( -1 );
	}
	result = libsystem_file_exists(
	          alias_path,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_LIBCSTRING_SYSTEM " exists.",
		 function,
		 alias_path );
	}
	else if( result == 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_GENERIC,
		 "%s: %" PRIs_LIBCSTRING_SYSTEM " already exists.",
		 function,
		 alias_path );
	}
	if( result != 0 )
	{
		memory_free(
		 alias_path );

		return( -1 );
	}
	if( export_handle_make_directory(
	     export_handle,
	     alias_path,
	     log_handle,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to create directory: %" PRIs_LIBCSTRING_SYSTEM "",
		 function,
		 alias_path );

		memory_free(
		 alias_path );

		return( -1 );
	}
	if( export_handle_export_item_values(
	     export_handle,
	     alias,
	     alias_path,
	     alias_path_size,
	     log_handle,
	     error ) != 1 )
	{
		if( libsystem_notify_verbose != 0 )
		{
			libsystem_notify_printf(
			 "%s: unable to export item values.\n",
			 function );
		}
		if( ( error != NULL )
		 && ( *error != NULL ) )
		{
			libsystem_notify_print_error_backtrace(
			 *error );
		}
		liberror_error_free(
		 error );

		log_handle_printf(
		 log_handle,
		 "Unable to export item values.\n" );
	}
#ifdef TODO
	/* Create the alias file
	 */
	if( export_handle_create_target_path(
	     export_handle,
	     alias_path,
	     alias_path_size,
	     (uint8_t *) "Alias.txt",
	     10,
	     &target_path,
	     &target_path_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create target path.",
		 function );

		memory_free(
		 alias_path );

		return( -1 );
	}
	if( target_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		memory_free(
		 alias_path );

		return( -1 );
	}
	result = libsystem_file_exists(
	          target_path,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_LIBCSTRING_SYSTEM " exists.",
		 function,
		 target_path );

		memory_free(
		 target_path );
		memory_free(
		 alias_path );

		return( -1 );
	}
	else if( result == 1 )
	{
		log_handle_printf(
		 log_handle,
		 "Skipping alias it already exists.\n" );

		memory_free(
		 target_path );
		memory_free(
		 alias_path );

		return( 1 );
	}
	alias_file_stream = libsystem_file_stream_open(
	                     target_path,
	                     _LIBCSTRING_SYSTEM_STRING( "w" ) );

	if( alias_file_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 target_path );

		memory_free(
		 target_path );
		memory_free(
		 alias_path );

		return( -1 );
	}
	memory_free(
	 target_path );

	/* TODO */

	/* Close the alias file
	 */
	if( libsystem_file_stream_close(
	     alias_file_stream ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close alias file.",
		 function );

		memory_free(
		 alias_path );

		return( -1 );
	}
#endif
	memory_free(
	 alias_path );

	return( 1 );
}

/* Exports the item values
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_item_values(
     export_handle_t *export_handle,
     libwtcdb_item_t *item,
     libcstring_system_character_t *export_path,
     size_t export_path_size,
     log_handle_t *log_handle,
     liberror_error_t **error )
{
	libcstring_system_character_t *target_path = NULL;
	FILE *item_values_file_stream      = NULL;
	uint8_t *value_data                = NULL;
	static char *function              = "export_handle_export_item_values";
	size_t target_path_size            = 0;
	size_t value_data_size             = 0;
	uint32_t number_of_entries         = 0;
	uint32_t entry_iterator            = 0;
	uint32_t entry_type                = 0;
	uint32_t value_type                = 0;
	int result                         = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( export_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
		 function );

		return( -1 );
	}
	/* Create the item value file
	 */
	if( export_handle_create_target_path(
	     export_handle,
	     export_path,
	     export_path_size,
	     (uint8_t *) "ItemValues.txt",
	     15,
	     &target_path,
	     &target_path_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create target path.",
		 function );

		return( -1 );
	}
	if( target_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		return( -1 );
	}
	result = libsystem_file_exists(
	          target_path,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_LIBCSTRING_SYSTEM " exists.",
		 function,
		 target_path );

		memory_free(
		 target_path );

		return( -1 );
	}
	else if( result == 1 )
	{
		memory_free(
		 target_path );

		return( 1 );
	}
	item_values_file_stream = libsystem_file_stream_open(
	                           target_path,
	                           _LIBCSTRING_SYSTEM_STRING( "w" ) );

	if( item_values_file_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 target_path );

		memory_free(
		 target_path );

		return( -1 );
	}
	memory_free(
	 target_path );

	if( libsystem_file_stream_close(
	     item_values_file_stream ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close item values file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Exports the file
 * Returns the 1 if succesful, 0 if no items are available or -1 on error
 */
int export_handle_export_file(
     export_handle_t *export_handle,
     libwtcdb_file_t *file,
     libcstring_system_character_t *export_path,
     size_t export_path_size,
     log_handle_t *log_handle,
     liberror_error_t **error )
{
	libwtcdb_item_t *item   = NULL;
	static char *function = "export_handle_export_file";
	int number_of_items   = 0;
	int item_iterator     = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( export_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		return( -1 );
	}
	if( libsystem_directory_make(
	     export_path ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: unable to make directory: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 function,
		 export_path );

		return( -1 );
	}
	if( libwtcdb_file_get_number_of_items(
	     file,
	     &number_of_items,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of items.",
		 function );

		return( -1 );
	}
	if( number_of_items == 0 )
	{
		return( 0 );
	}
	for( item_iterator = 0;
	     item_iterator < number_of_items;
	     item_iterator++ )
	{
		if( libwtcdb_file_get_item(
		     file,
		     item_iterator,
		     &item,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve item: %d.",
			 function,
			 item_iterator + 1 );

			return( -1 );
		}
		if( export_handle_export_alias(
		     export_handle,
		     item,
		     item_iterator,
		     number_of_items,
		     export_path,
		     export_path_size,
		     log_handle,
		     error ) != 1 )
		{
			fprintf(
			 stdout,
			 "Unable to export alias %d out of %d.\n",
			 item_iterator + 1,
			 number_of_items );

			if( libsystem_notify_verbose != 0 )
			{
				libsystem_notify_printf(
				 "%s: unable to export alias: %d.\n",
				 function,
				 item_iterator + 1 );
			}
			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libsystem_notify_print_error_backtrace(
				 *error );
			}
			liberror_error_free(
			 error );
		}
		if( libwtcdb_item_free(
		     &item,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free item: %d.",
			 function,
			 item_iterator + 1 );

			return( -1 );
		}
	}
	return( 1 );
}

