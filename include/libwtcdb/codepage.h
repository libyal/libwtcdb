/*
 * Codepage definitions for libwtcdb
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

#if !defined( _LIBWTCDB_CODEPAGE_H )
#define _LIBWTCDB_CODEPAGE_H

#include <libwtcdb/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBWTCDB_CODEPAGES
{
	LIBWTCDB_CODEPAGE_ASCII				= 20127,

	LIBWTCDB_CODEPAGE_ISO_8859_1			= 28591,
	LIBWTCDB_CODEPAGE_ISO_8859_2			= 28592,
	LIBWTCDB_CODEPAGE_ISO_8859_3			= 28593,
	LIBWTCDB_CODEPAGE_ISO_8859_4			= 28594,
	LIBWTCDB_CODEPAGE_ISO_8859_5			= 28595,
	LIBWTCDB_CODEPAGE_ISO_8859_6			= 28596,
	LIBWTCDB_CODEPAGE_ISO_8859_7			= 28597,
	LIBWTCDB_CODEPAGE_ISO_8859_8			= 28598,
	LIBWTCDB_CODEPAGE_ISO_8859_9			= 28599,
	LIBWTCDB_CODEPAGE_ISO_8859_10			= 28600,
	LIBWTCDB_CODEPAGE_ISO_8859_11			= 28601,
	LIBWTCDB_CODEPAGE_ISO_8859_13			= 28603,
	LIBWTCDB_CODEPAGE_ISO_8859_14			= 28604,
	LIBWTCDB_CODEPAGE_ISO_8859_15			= 28605,
	LIBWTCDB_CODEPAGE_ISO_8859_16			= 28606,

	LIBWTCDB_CODEPAGE_KOI8_R			= 20866,
	LIBWTCDB_CODEPAGE_KOI8_U			= 21866,

	LIBWTCDB_CODEPAGE_WINDOWS_874			= 874,
	LIBWTCDB_CODEPAGE_WINDOWS_932			= 932,
	LIBWTCDB_CODEPAGE_WINDOWS_936			= 936,
	LIBWTCDB_CODEPAGE_WINDOWS_949			= 949,
	LIBWTCDB_CODEPAGE_WINDOWS_950			= 950,
	LIBWTCDB_CODEPAGE_WINDOWS_1250			= 1250,
	LIBWTCDB_CODEPAGE_WINDOWS_1251			= 1251,
	LIBWTCDB_CODEPAGE_WINDOWS_1252			= 1252,
	LIBWTCDB_CODEPAGE_WINDOWS_1253			= 1253,
	LIBWTCDB_CODEPAGE_WINDOWS_1254			= 1254,
	LIBWTCDB_CODEPAGE_WINDOWS_1255			= 1255,
	LIBWTCDB_CODEPAGE_WINDOWS_1256			= 1256,
	LIBWTCDB_CODEPAGE_WINDOWS_1257			= 1257,
	LIBWTCDB_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBWTCDB_CODEPAGE_US_ASCII			LIBWTCDB_CODEPAGE_ASCII

#define LIBWTCDB_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBWTCDB_CODEPAGE_ISO_8859_1
#define LIBWTCDB_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBWTCDB_CODEPAGE_ISO_8859_2
#define LIBWTCDB_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBWTCDB_CODEPAGE_ISO_8859_3
#define LIBWTCDB_CODEPAGE_ISO_NORTH_EUROPEAN		LIBWTCDB_CODEPAGE_ISO_8859_4
#define LIBWTCDB_CODEPAGE_ISO_CYRILLIC			LIBWTCDB_CODEPAGE_ISO_8859_5
#define LIBWTCDB_CODEPAGE_ISO_ARABIC			LIBWTCDB_CODEPAGE_ISO_8859_6
#define LIBWTCDB_CODEPAGE_ISO_GREEK			LIBWTCDB_CODEPAGE_ISO_8859_7
#define LIBWTCDB_CODEPAGE_ISO_HEBREW			LIBWTCDB_CODEPAGE_ISO_8859_8
#define LIBWTCDB_CODEPAGE_ISO_TURKISH			LIBWTCDB_CODEPAGE_ISO_8859_9
#define LIBWTCDB_CODEPAGE_ISO_NORDIC			LIBWTCDB_CODEPAGE_ISO_8859_10
#define LIBWTCDB_CODEPAGE_ISO_THAI			LIBWTCDB_CODEPAGE_ISO_8859_11
#define LIBWTCDB_CODEPAGE_ISO_BALTIC			LIBWTCDB_CODEPAGE_ISO_8859_13
#define LIBWTCDB_CODEPAGE_ISO_CELTIC			LIBWTCDB_CODEPAGE_ISO_8859_14

#define LIBWTCDB_CODEPAGE_ISO_LATIN_1			LIBWTCDB_CODEPAGE_ISO_8859_1
#define LIBWTCDB_CODEPAGE_ISO_LATIN_2			LIBWTCDB_CODEPAGE_ISO_8859_2
#define LIBWTCDB_CODEPAGE_ISO_LATIN_3			LIBWTCDB_CODEPAGE_ISO_8859_3
#define LIBWTCDB_CODEPAGE_ISO_LATIN_4			LIBWTCDB_CODEPAGE_ISO_8859_4
#define LIBWTCDB_CODEPAGE_ISO_LATIN_5			LIBWTCDB_CODEPAGE_ISO_8859_9
#define LIBWTCDB_CODEPAGE_ISO_LATIN_6			LIBWTCDB_CODEPAGE_ISO_8859_10
#define LIBWTCDB_CODEPAGE_ISO_LATIN_7			LIBWTCDB_CODEPAGE_ISO_8859_13
#define LIBWTCDB_CODEPAGE_ISO_LATIN_8			LIBWTCDB_CODEPAGE_ISO_8859_14
#define LIBWTCDB_CODEPAGE_ISO_LATIN_9			LIBWTCDB_CODEPAGE_ISO_8859_15
#define LIBWTCDB_CODEPAGE_ISO_LATIN_10			LIBWTCDB_CODEPAGE_ISO_8859_16

#define LIBWTCDB_CODEPAGE_KOI8_RUSSIAN			LIBWTCDB_CODEPAGE_KOI8_R
#define LIBWTCDB_CODEPAGE_KOI8_UKRAINIAN		LIBWTCDB_CODEPAGE_KOI8_U

#define LIBWTCDB_CODEPAGE_WINDOWS_THAI			LIBWTCDB_CODEPAGE_WINDOWS_874
#define LIBWTCDB_CODEPAGE_WINDOWS_JAPANESE		LIBWTCDB_CODEPAGE_WINDOWS_932
#define LIBWTCDB_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBWTCDB_CODEPAGE_WINDOWS_936
#define LIBWTCDB_CODEPAGE_WINDOWS_KOREAN		LIBWTCDB_CODEPAGE_WINDOWS_949
#define LIBWTCDB_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBWTCDB_CODEPAGE_WINDOWS_950
#define LIBWTCDB_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBWTCDB_CODEPAGE_WINDOWS_1250
#define LIBWTCDB_CODEPAGE_WINDOWS_CYRILLIC		LIBWTCDB_CODEPAGE_WINDOWS_1251
#define LIBWTCDB_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBWTCDB_CODEPAGE_WINDOWS_1252
#define LIBWTCDB_CODEPAGE_WINDOWS_GREEK			LIBWTCDB_CODEPAGE_WINDOWS_1253
#define LIBWTCDB_CODEPAGE_WINDOWS_TURKISH		LIBWTCDB_CODEPAGE_WINDOWS_1254
#define LIBWTCDB_CODEPAGE_WINDOWS_HEBREW		LIBWTCDB_CODEPAGE_WINDOWS_1255
#define LIBWTCDB_CODEPAGE_WINDOWS_ARABIC		LIBWTCDB_CODEPAGE_WINDOWS_1256
#define LIBWTCDB_CODEPAGE_WINDOWS_BALTIC		LIBWTCDB_CODEPAGE_WINDOWS_1257
#define LIBWTCDB_CODEPAGE_WINDOWS_VIETNAMESE		LIBWTCDB_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWTCDB_CODEPAGE_H ) */

