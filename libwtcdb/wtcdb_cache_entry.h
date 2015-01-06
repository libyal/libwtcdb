/*
 * The cache entry definition of a Windows Explorer thumbnail cache database file
 *
 * Copyright (C) 2010-2015, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _WTCDB_CACHE_ENTRY_H )
#define _WTCDB_CACHE_ENTRY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct wtcdb_cache_entry_vista wtcdb_cache_entry_vista_t;

struct wtcdb_cache_entry_vista
{
	/* Signature
	 * Consists of 4 bytes
	 * Contains CMMM
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The entry hash
	 * Consists of 8 bytes
	 */
	uint8_t entry_hash[ 8 ];

	/* The file extension
	 * Consists of 8 bytes
	 * Contains an UTF-16 little-endian string
	 */
	uint8_t file_extension[ 8 ];

	/* The identifier string size
	 * Consists of 4 bytes
	 */
	uint8_t identifier_string_size[ 4 ];

	/* Padding size
	 * Consists of 4 bytes
	 */
	uint8_t padding_size[ 4 ];

	/* The data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* A CRC-64 of the data
	 * Consists of 8 bytes
	 */
	uint8_t data_checksum[ 8 ];

	/* A CRC-64 of the header
	 * Consists of 8 bytes
	 */
	uint8_t header_checksum[ 8 ];

	/* The identifier string
	 */

	/* The data
	 */
};

typedef struct wtcdb_cache_entry_win7 wtcdb_cache_entry_win7_t;

struct wtcdb_cache_entry_win7
{
	/* Signature
	 * Consists of 4 bytes
	 * Contains CMMM
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The entry hash
	 * Consists of 8 bytes
	 */
	uint8_t entry_hash[ 8 ];

	/* The identifier string size
	 * Consists of 4 bytes
	 */
	uint8_t identifier_string_size[ 4 ];

	/* Padding size
	 * Consists of 4 bytes
	 */
	uint8_t padding_size[ 4 ];

	/* The data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* A CRC-64 of the data
	 * Consists of 8 bytes
	 */
	uint8_t data_checksum[ 8 ];

	/* A CRC-64 of the header
	 * Consists of 8 bytes
	 */
	uint8_t header_checksum[ 8 ];

	/* The identifier string
	 */

	/* The data
	 */
};

#if defined( __cplusplus )
}
#endif

#endif

