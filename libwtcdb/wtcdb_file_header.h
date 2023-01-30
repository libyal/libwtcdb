/*
 * The file header definition of a Windows Explorer thumbnail cache database file
 *
 * Copyright (C) 2010-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _WTCDB_FILE_HEADER_H )
#define _WTCDB_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct wtcdb_cache_file_header wtcdb_cache_file_header_t;

struct wtcdb_cache_file_header
{
	/* Signature
	 * Consists of 4 bytes
	 * Contains CMMM
	 */
	uint8_t signature[ 4 ];

	/* Format version
	 * Consists of 4 bytes
	 */
	uint8_t format_version[ 4 ];

	/* Cache type
	 * Consists of 4 bytes
	 */
	uint8_t cache_type[ 4 ];

	/* Offset to the first cache entry
	 * Consists of 4 bytes
	 */
	uint8_t first_cache_entry_offset[ 4 ];

	/* Offset to the (next) available cache entry
	 * Consists of 4 bytes
	 */
	uint8_t available_cache_entry_offset[ 4 ];

	/* Number of cache entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_cache_entries[ 4 ];
};

typedef struct wtcdb_index_file_header wtcdb_index_file_header_t;

struct wtcdb_index_file_header
{
	/* Signature
	 * Consists of 4 bytes
	 * Contains IMMM
	 */
	uint8_t signature[ 4 ];

	/* Format version
	 * Consists of 4 bytes
	 */
	uint8_t format_version[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The number of index entries used
	 * Consists of 4 bytes
	 */
	uint8_t number_of_index_entries_used[ 4 ];

	/* Total number of index entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_index_entries[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _WTCDB_FILE_HEADER_H ) */

