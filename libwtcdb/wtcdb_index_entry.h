/*
 * The index entry definition of a Windows Explorer thumbnail index database file
 *
 * Copyright (C) 2010-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _WTCDB_INDEX_ENTRY_H )
#define _WTCDB_INDEX_ENTRY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct wtcdb_index_entry_vista wtcdb_index_entry_vista_t;

struct wtcdb_index_entry_vista
{
	/* The entry hash
	 * Consists of 8 bytes
	 */
	uint8_t entry_hash[ 8 ];

	/* Last modification date and time
	 * Consists of 8 bytes
	 * Contains a filetime
	 */
	uint8_t modification_time[ 8 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Cache entry offset for thumbcache_32.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_32[ 4 ];

	/* Cache entry offset for thumbcache_96.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_96[ 4 ];

	/* Cache entry offset for thumbcache_256.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_256[ 4 ];

	/* Cache entry offset for thumbcache_1024.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_1024[ 4 ];

	/* Cache entry offset for thumbcache_sr.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_sr[ 4 ];
};

typedef struct wtcdb_index_entry_win7 wtcdb_index_entry_win7_t;

struct wtcdb_index_entry_win7
{
	/* The entry hash
	 * Consists of 8 bytes
	 */
	uint8_t entry_hash[ 8 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Cache entry offset for thumbcache_32.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_32[ 4 ];

	/* Cache entry offset for thumbcache_96.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_96[ 4 ];

	/* Cache entry offset for thumbcache_256.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_256[ 4 ];

	/* Cache entry offset for thumbcache_1024.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_1024[ 4 ];

	/* Cache entry offset for thumbcache_sr.db
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_offset_sr[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif

