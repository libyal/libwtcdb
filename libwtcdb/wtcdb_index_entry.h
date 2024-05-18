/*
 * The index entry definition of a Windows Explorer thumbnail index database file
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _WTCDB_INDEX_ENTRY_H )
#define _WTCDB_INDEX_ENTRY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct wtcdb_index_entry_v20 wtcdb_index_entry_v20_t;

struct wtcdb_index_entry_v20
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

	/* Cache entry offsets
	 * Consists of 5 x 4 bytes
	 */
	uint8_t cache_entry_offsets[ 20 ];
};

typedef struct wtcdb_index_entry_v21 wtcdb_index_entry_v21_t;

struct wtcdb_index_entry_v21
{
	/* The entry hash
	 * Consists of 8 bytes
	 */
	uint8_t entry_hash[ 8 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Cache entry offsets
	 * Consists of 5 x 4 bytes
	 */
	uint8_t cache_entry_offsets[ 20 ];
};

typedef struct wtcdb_index_entry_v30 wtcdb_index_entry_v30_t;

struct wtcdb_index_entry_v30
{
	/* The entry hash
	 * Consists of 8 bytes
	 */
	uint8_t entry_hash[ 8 ];

	/* Flags
	 * Consists of 8 bytes
	 */
	uint8_t flags[ 8 ];

	/* Cache entry offsets
	 * Consists of 9 x 4 bytes
	 */
	uint8_t cache_entry_offsets[ 36 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];
};

typedef struct wtcdb_index_entry_v31 wtcdb_index_entry_v31_t;

struct wtcdb_index_entry_v31
{
	/* The entry hash
	 * Consists of 8 bytes
	 */
	uint8_t entry_hash[ 8 ];

	/* Flags
	 * Consists of 8 bytes
	 */
	uint8_t flags[ 8 ];

	/* Cache entry offsets
	 * Consists of 11 x 4 bytes
	 */
	uint8_t cache_entry_offsets[ 44 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];
};

typedef struct wtcdb_index_entry_v32 wtcdb_index_entry_v32_t;

struct wtcdb_index_entry_v32
{
	/* The entry hash
	 * Consists of 8 bytes
	 */
	uint8_t entry_hash[ 8 ];

	/* Flags
	 * Consists of 8 bytes
	 */
	uint8_t flags[ 8 ];

	/* Cache entry offsets
	 * Consists of 14 x 4 bytes
	 */
	uint8_t cache_entry_offsets[ 56 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _WTCDB_INDEX_ENTRY_H ) */

