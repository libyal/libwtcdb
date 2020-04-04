/*
 * CRC-64 functions
 *
 * Copyright (C) 2010-2020, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <types.h>

#include "libwtcdb_libcerror.h"

/* Table of CRC-64 values of 8-bit values */
const uint64_t libwtcdb_crc64_table[ 256 ] = {
	0x0000000000000000ULL, 0x0809e8a2969451e9ULL, 0x1013d1452d28a3d2ULL, 0x181a39e7bbbcf23bULL,
	0x2027a28a5a5147a4ULL, 0x282e4a28ccc5164dULL, 0x303473cf7779e476ULL, 0x383d9b6de1edb59fULL,
	0x404f4514b4a28f48ULL, 0x4846adb62236dea1ULL, 0x505c9451998a2c9aULL, 0x58557cf30f1e7d73ULL,
	0x6068e79eeef3c8ecULL, 0x68610f3c78679905ULL, 0x707b36dbc3db6b3eULL, 0x7872de79554f3ad7ULL,
	0x809e8a2969451e90ULL, 0x8897628bffd14f79ULL, 0x908d5b6c446dbd42ULL, 0x9884b3ced2f9ecabULL,
	0xa0b928a333145934ULL, 0xa8b0c001a58008ddULL, 0xb0aaf9e61e3cfae6ULL, 0xb8a3114488a8ab0fULL,
	0xc0d1cf3ddde791d8ULL, 0xc8d8279f4b73c031ULL, 0xd0c21e78f0cf320aULL, 0xd8cbf6da665b63e3ULL,
	0xe0f66db787b6d67cULL, 0xe8ff851511228795ULL, 0xf0e5bcf2aa9e75aeULL, 0xf8ec54503c0a2447ULL,
	0x24b1909974c84e69ULL, 0x2cb8783be25c1f80ULL, 0x34a241dc59e0edbbULL, 0x3caba97ecf74bc52ULL,
	0x049632132e9909cdULL, 0x0c9fdab1b80d5824ULL, 0x1485e35603b1aa1fULL, 0x1c8c0bf49525fbf6ULL,
	0x64fed58dc06ac121ULL, 0x6cf73d2f56fe90c8ULL, 0x74ed04c8ed4262f3ULL, 0x7ce4ec6a7bd6331aULL,
	0x44d977079a3b8685ULL, 0x4cd09fa50cafd76cULL, 0x54caa642b7132557ULL, 0x5cc34ee0218774beULL,
	0xa42f1ab01d8d50f9ULL, 0xac26f2128b190110ULL, 0xb43ccbf530a5f32bULL, 0xbc352357a631a2c2ULL,
	0x8408b83a47dc175dULL, 0x8c015098d14846b4ULL, 0x941b697f6af4b48fULL, 0x9c1281ddfc60e566ULL,
	0xe4605fa4a92fdfb1ULL, 0xec69b7063fbb8e58ULL, 0xf4738ee184077c63ULL, 0xfc7a664312932d8aULL,
	0xc447fd2ef37e9815ULL, 0xcc4e158c65eac9fcULL, 0xd4542c6bde563bc7ULL, 0xdc5dc4c948c26a2eULL,
	0x49632132e9909cd2ULL, 0x416ac9907f04cd3bULL, 0x5970f077c4b83f00ULL, 0x517918d5522c6ee9ULL,
	0x694483b8b3c1db76ULL, 0x614d6b1a25558a9fULL, 0x795752fd9ee978a4ULL, 0x715eba5f087d294dULL,
	0x092c64265d32139aULL, 0x01258c84cba64273ULL, 0x193fb563701ab048ULL, 0x11365dc1e68ee1a1ULL,
	0x290bc6ac0763543eULL, 0x21022e0e91f705d7ULL, 0x391817e92a4bf7ecULL, 0x3111ff4bbcdfa605ULL,
	0xc9fdab1b80d58242ULL, 0xc1f443b91641d3abULL, 0xd9ee7a5eadfd2190ULL, 0xd1e792fc3b697079ULL,
	0xe9da0991da84c5e6ULL, 0xe1d3e1334c10940fULL, 0xf9c9d8d4f7ac6634ULL, 0xf1c03076613837ddULL,
	0x89b2ee0f34770d0aULL, 0x81bb06ada2e35ce3ULL, 0x99a13f4a195faed8ULL, 0x91a8d7e88fcbff31ULL,
	0xa9954c856e264aaeULL, 0xa19ca427f8b21b47ULL, 0xb9869dc0430ee97cULL, 0xb18f7562d59ab895ULL,
	0x6dd2b1ab9d58d2bbULL, 0x65db59090bcc8352ULL, 0x7dc160eeb0707169ULL, 0x75c8884c26e42080ULL,
	0x4df51321c709951fULL, 0x45fcfb83519dc4f6ULL, 0x5de6c264ea2136cdULL, 0x55ef2ac67cb56724ULL,
	0x2d9df4bf29fa5df3ULL, 0x25941c1dbf6e0c1aULL, 0x3d8e25fa04d2fe21ULL, 0x3587cd589246afc8ULL,
	0x0dba563573ab1a57ULL, 0x05b3be97e53f4bbeULL, 0x1da987705e83b985ULL, 0x15a06fd2c817e86cULL,
	0xed4c3b82f41dcc2bULL, 0xe545d32062899dc2ULL, 0xfd5feac7d9356ff9ULL, 0xf55602654fa13e10ULL,
	0xcd6b9908ae4c8b8fULL, 0xc56271aa38d8da66ULL, 0xdd78484d8364285dULL, 0xd571a0ef15f079b4ULL,
	0xad037e9640bf4363ULL, 0xa50a9634d62b128aULL, 0xbd10afd36d97e0b1ULL, 0xb5194771fb03b158ULL,
	0x8d24dc1c1aee04c7ULL, 0x852d34be8c7a552eULL, 0x9d370d5937c6a715ULL, 0x953ee5fba152f6fcULL,
	0x92c64265d32139a4ULL, 0x9acfaac745b5684dULL, 0x82d59320fe099a76ULL, 0x8adc7b82689dcb9fULL,
	0xb2e1e0ef89707e00ULL, 0xbae8084d1fe42fe9ULL, 0xa2f231aaa458ddd2ULL, 0xaafbd90832cc8c3bULL,
	0xd28907716783b6ecULL, 0xda80efd3f117e705ULL, 0xc29ad6344aab153eULL, 0xca933e96dc3f44d7ULL,
	0xf2aea5fb3dd2f148ULL, 0xfaa74d59ab46a0a1ULL, 0xe2bd74be10fa529aULL, 0xeab49c1c866e0373ULL,
	0x1258c84cba642734ULL, 0x1a5120ee2cf076ddULL, 0x024b1909974c84e6ULL, 0x0a42f1ab01d8d50fULL,
	0x327f6ac6e0356090ULL, 0x3a76826476a13179ULL, 0x226cbb83cd1dc342ULL, 0x2a6553215b8992abULL,
	0x52178d580ec6a87cULL, 0x5a1e65fa9852f995ULL, 0x42045c1d23ee0baeULL, 0x4a0db4bfb57a5a47ULL,
	0x72302fd25497efd8ULL, 0x7a39c770c203be31ULL, 0x6223fe9779bf4c0aULL, 0x6a2a1635ef2b1de3ULL,
	0xb677d2fca7e977cdULL, 0xbe7e3a5e317d2624ULL, 0xa66403b98ac1d41fULL, 0xae6deb1b1c5585f6ULL,
	0x96507076fdb83069ULL, 0x9e5998d46b2c6180ULL, 0x8643a133d09093bbULL, 0x8e4a49914604c252ULL,
	0xf63897e8134bf885ULL, 0xfe317f4a85dfa96cULL, 0xe62b46ad3e635b57ULL, 0xee22ae0fa8f70abeULL,
	0xd61f3562491abf21ULL, 0xde16ddc0df8eeec8ULL, 0xc60ce42764321cf3ULL, 0xce050c85f2a64d1aULL,
	0x36e958d5ceac695dULL, 0x3ee0b077583838b4ULL, 0x26fa8990e384ca8fULL, 0x2ef3613275109b66ULL,
	0x16cefa5f94fd2ef9ULL, 0x1ec712fd02697f10ULL, 0x06dd2b1ab9d58d2bULL, 0x0ed4c3b82f41dcc2ULL,
	0x76a61dc17a0ee615ULL, 0x7eaff563ec9ab7fcULL, 0x66b5cc84572645c7ULL, 0x6ebc2426c1b2142eULL,
	0x5681bf4b205fa1b1ULL, 0x5e8857e9b6cbf058ULL, 0x46926e0e0d770263ULL, 0x4e9b86ac9be3538aULL,
	0xdba563573ab1a576ULL, 0xd3ac8bf5ac25f49fULL, 0xcbb6b212179906a4ULL, 0xc3bf5ab0810d574dULL,
	0xfb82c1dd60e0e2d2ULL, 0xf38b297ff674b33bULL, 0xeb9110984dc84100ULL, 0xe398f83adb5c10e9ULL,
	0x9bea26438e132a3eULL, 0x93e3cee118877bd7ULL, 0x8bf9f706a33b89ecULL, 0x83f01fa435afd805ULL,
	0xbbcd84c9d4426d9aULL, 0xb3c46c6b42d63c73ULL, 0xabde558cf96ace48ULL, 0xa3d7bd2e6ffe9fa1ULL,
	0x5b3be97e53f4bbe6ULL, 0x533201dcc560ea0fULL, 0x4b28383b7edc1834ULL, 0x4321d099e84849ddULL,
	0x7b1c4bf409a5fc42ULL, 0x7315a3569f31adabULL, 0x6b0f9ab1248d5f90ULL, 0x63067213b2190e79ULL,
	0x1b74ac6ae75634aeULL, 0x137d44c871c26547ULL, 0x0b677d2fca7e977cULL, 0x036e958d5ceac695ULL,
	0x3b530ee0bd07730aULL, 0x335ae6422b9322e3ULL, 0x2b40dfa5902fd0d8ULL, 0x2349370706bb8131ULL,
	0xff14f3ce4e79eb1fULL, 0xf71d1b6cd8edbaf6ULL, 0xef07228b635148cdULL, 0xe70eca29f5c51924ULL,
	0xdf3351441428acbbULL, 0xd73ab9e682bcfd52ULL, 0xcf20800139000f69ULL, 0xc72968a3af945e80ULL,
	0xbf5bb6dafadb6457ULL, 0xb7525e786c4f35beULL, 0xaf48679fd7f3c785ULL, 0xa7418f3d4167966cULL,
	0x9f7c1450a08a23f3ULL, 0x9775fcf2361e721aULL, 0x8f6fc5158da28021ULL, 0x87662db71b36d1c8ULL,
	0x7f8a79e7273cf58fULL, 0x77839145b1a8a466ULL, 0x6f99a8a20a14565dULL, 0x679040009c8007b4ULL,
	0x5faddb6d7d6db22bULL, 0x57a433cfebf9e3c2ULL, 0x4fbe0a28504511f9ULL, 0x47b7e28ac6d14010ULL,
	0x3fc53cf3939e7ac7ULL, 0x37ccd451050a2b2eULL, 0x2fd6edb6beb6d915ULL, 0x27df0514282288fcULL,
	0x1fe29e79c9cf3d63ULL, 0x17eb76db5f5b6c8aULL, 0x0ff14f3ce4e79eb1ULL, 0x07f8a79e7273cf58ULL
};

/* Calculates the weak CRC-64 of a buffer
 * Use a previous key of 0 to calculate a new CRC-64
 * Returns 1 if successful or -1 on error
 */
int libwtcdb_crc64_weak_calculate(
     uint64_t *crc64,
     const uint8_t *buffer,
     size_t size,
     uint64_t initial_value,
     libcerror_error_t **error )
{
	static char *function      = "libwtcdb_crc64_weak_calculate";
	size_t buffer_offset       = 0;
	uint64_t crc64_table_index = 0;

	if( crc64 == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid CRC-64.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	*crc64 = initial_value;

        for( buffer_offset = 0;
	     buffer_offset < size;
	     buffer_offset++ )
	{
		crc64_table_index = ( *crc64 ^ buffer[ buffer_offset ] ) & (uint64_t) 0x00000000000000ffULL;

		*crc64 = libwtcdb_crc64_table[ crc64_table_index ] ^ ( *crc64 >> 8 );
        }
	return( 1 );
}

