/*
 * The file header definition of a Windows Explorer thumbnail cache database file
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

#if !defined( _WTCDB_FILE_HEADER_H )
#define _WTCDB_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct wtcdb_file_header wtcdb_file_header_t;

struct wtcdb_file_header
{
	/* Signature
	 * Consists of 4 bytes
	 * Contains CMMM for a database file
	 * Contains IMMM for an index file
	 */
	uint8_t signature[ 4 ];

	/* Version
	 * Consists of 4 bytes
	 */
	uint8_t version[ 4 ];

	/* Cache type
	 * Consists of 4 bytes
	 */
	uint8_t cache_type[ 4 ];

	/* Offset to the first thumbnail entry
	 * Consists of 4 bytes
	 */
	uint8_t first_thumbnail_entry_offset[ 4 ];

	/* Offset to the next (available) thumbnail entry
	 * Consists of 4 bytes
	 */
	uint8_t next_thumbnail_entry_offset[ 4 ];

	/* Number of thumbnail entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_thumbnail_entries[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif

