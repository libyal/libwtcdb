/*
 * Internationalization (i18n) functions
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

#if !defined( _WTCDBTOOLS_I18N_H )
#define _WTCDBTOOLS_I18N_H

#include <common.h>

#if defined( HAVE_LIBINTL_H )
#include <libintl.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* TODO for now do nothing i18n-like
#define	_( string ) \
	gettext( string )
*/

#define	_( string ) \
	string

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _WTCDBTOOLS_I18N_H ) */

