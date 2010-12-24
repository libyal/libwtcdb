/* 
 * Export handle
 *
 * Copyright (c) 2010, Joachim Metz <jbmetz@users.sourceforge.net>
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
		*export_handle = memory_allocate_structure(
		                  export_handle_t );

		if( *export_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create export handle.",
			 function );

			goto on_error;
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

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( *export_handle != NULL )
	{
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( -1 );
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
		if( ( *export_handle )->target_path != NULL )
		{
			memory_free(
			 ( *export_handle )->target_path );
		}
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

		goto on_error;
	}
	/* Include space for the separator and the end of string character
	 */
	*target_path_size = export_path_size + filename_size;

	*target_path = libcstring_system_string_allocate(
	                *target_path_size );

	if( *target_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create target path.",
		 function );

		goto on_error;
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

		goto on_error;
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

		goto on_error;
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

		goto on_error;
	}
	return( 1 );

on_error:
	if( *target_path != NULL )
	{
		memory_free(
		 target_path );

		*target_path = NULL;
	}
	*target_path_size = 0;

	return( -1 );
}

/* Sets an export path consisting of a base path and a suffix
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_export_path(
     export_handle_t *export_handle,
     const libcstring_system_character_t *base_path,
     size_t base_path_length,
     const libcstring_system_character_t *suffix,
     size_t suffix_length,
     libcstring_system_character_t **export_path,
     size_t *export_path_size,
     liberror_error_t **error )
{
	static char *function = "export_handle_set_export_path";

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
	if( base_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base path.",
		 function );

		return( -1 );
	}
	if( base_path_length > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( suffix == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid suffix.",
		 function );

		return( -1 );
	}
	if( suffix_length > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid suffix length value exceeds maximum.",
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
	if( export_path_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path size.",
		 function );

		return( -1 );
	}
	if( *export_path != NULL )
	{
		memory_free(
		 *export_path );

		*export_path      = NULL;
		*export_path_size = 0;
	}
	*export_path_size = base_path_length + suffix_length + 1;

	*export_path = libcstring_system_string_allocate(
	                *export_path_size );

	if( *export_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create export path.",
		 function );

		goto on_error;
	}
	if( libcstring_system_string_copy(
	     *export_path,
	     base_path,
	     base_path_length ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy base path to item export path.",
		 function );

		goto on_error;
	}
	if( libcstring_system_string_copy(
	     &( ( *export_path )[ base_path_length ] ),
	     suffix,
	     suffix_length ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy suffix to item export path.",
		 function );

		goto on_error;
	}
	( *export_path )[ *export_path_size - 1 ] = 0;

	return( 1 );

on_error:
	if( *export_path != NULL )
	{
		memory_free(
		 *export_path );

		*export_path      = NULL;
		*export_path_size = 0;
	}
	return( -1 );
}

/* Creates the export path
 * Returns 1 if successful, 0 if already exists or -1 on error
 */
int export_handle_create_export_path(
     export_handle_t *export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_create_export_path";
	int result            = 0;

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
	if( export_handle_set_export_path(
	     export_handle,
	     export_handle->target_path,
	     export_handle->target_path_size - 1,
	     _LIBCSTRING_SYSTEM_STRING( ".export" ),
	     7,
	     &( export_handle->export_path ),
	     &( export_handle->export_path_size ),
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set export path.",
		 function );

		return( -1 );
	}
	result = libsystem_file_exists(
		  export_handle->export_path,
		  error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_LIBCSTRING_SYSTEM " exists.",
		 function,
		 export_handle->export_path );

		return( -1 );
	}
	else if( result == 1 )
	{
		return( 0 );
	}
	return( 1 );
}

/* Sets the target path
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_target_path(
     export_handle_t *export_handle,
     const libcstring_system_character_t *target_path,
     liberror_error_t **error )
{
	static char *function                                      = "export_handle_set_target_path";
	size_t target_path_length                                  = 0;

#if defined( WINAPI )
	libcstring_system_character_t *extended_length_target_path = NULL;
        size_t extended_length_target_path_size                    = 0;
	int result                                                 = 0;
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
	if( export_handle->target_path != NULL )
	{
		memory_free(
		 export_handle->target_path );

		export_handle->target_path      = NULL;
		export_handle->target_path_size = 0;
	}
	target_path_length = libcstring_system_string_length(
	                      target_path );

#if defined( WINAPI )
	result = libsystem_file_create_windows_extended_path(
	          target_path,
                  target_path_length,
                  &extended_length_target_path,
                  &extended_length_target_path_size,
                  error );

        if( result == -1 )
        {
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create extended-length target path.",
		 function );

		return( -1 );
        }
        else if( result != 0 )
        {
                target_path        = extended_length_target_path;
                target_path_length = extended_length_target_path_size - 1;
        }
#endif
	if( target_path_length > 0 )
	{
		export_handle->target_path = (libcstring_system_character_t *) memory_allocate(
		                                                                sizeof( libcstring_system_character_t ) * ( target_path_length + 1 ) );

		if( export_handle->target_path == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create target path.",
			 function );

#if defined( WINAPI )
			memory_free(
			 extended_length_target_path );
#endif
			return( -1 );
		}
		if( libcstring_system_string_copy(
		     export_handle->target_path,
		     target_path,
		     target_path_length ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy target path.",
			 function );

#if defined( WINAPI )
			memory_free(
			 extended_length_target_path );
#endif
			memory_free(
			 export_handle->target_path );

			export_handle->target_path = NULL;

			return( -1 );
		}
		( export_handle->target_path )[ target_path_length ] = 0;

		export_handle->target_path_size = target_path_length + 1;
	}
#if defined( WINAPI )
	memory_free(
	 extended_length_target_path );
#endif
	return( 1 );
}

/* Exports the file
 * Returns the 1 if succesful, 0 if no items are available or -1 on error
 */
int export_handle_export_file(
     export_handle_t *export_handle,
     libwtcdb_file_t *file,
     log_handle_t *log_handle,
     liberror_error_t **error )
{
	libwtcdb_item_t *item = NULL;
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
	if( libsystem_directory_make(
	     export_handle->export_path ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: unable to make directory: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 function,
		 export_handle->export_path );

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
/* TODO
		if( export_handle_export_thumbnail(
		     export_handle,
		     item,
		     item_iterator,
		     number_of_items,
		     log_handle,
		     error ) != 1 )
		{
			fprintf(
			 stdout,
			 "Unable to export thumbnail %d out of %d.\n",
			 item_iterator + 1,
			 number_of_items );

			if( libsystem_notify_verbose != 0 )
			{
				libsystem_notify_printf(
				 "%s: unable to export thumbnail: %d.\n",
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
*/
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

