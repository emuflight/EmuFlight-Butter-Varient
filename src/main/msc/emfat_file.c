/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Author: jflyper@github.com
 */

#include "common/utils.h"
#include "common/printf.h"

#include "emfat.h"
#include "emfat_file.h"

#include "io/flashfs.h"

#define FILESYSTEM_SIZE_MB 256

#define USE_EMFAT_AUTORUN
#define USE_EMFAT_ICON
//#define USE_EMFAT_README

#ifdef USE_EMFAT_AUTORUN
static const char autorun_file[] =
    "[autorun]\r\n"
    "icon=icon.ico\r\n"
    "label=EgoFlight Onboard Flash\r\n" ;
#define AUTORUN_SIZE (sizeof(autorun_file) - 1)
#define EMFAT_INCR_AUTORUN 1
#else
#define EMFAT_INCR_AUTORUN 0
#endif

#ifdef USE_EMFAT_README
static const char readme_file[] =
    "This is readme file\r\n";
#define README_SIZE  (sizeof(readme_file) - 1)
#define EMFAT_INCR_README 1
#else
#define EMFAT_INCR_README 0
#endif

#ifdef USE_EMFAT_ICON
static const char icon_file[] =
{
    0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x18, 0x18, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x88, 0x09,
    0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xef, 0xae, 0x00, 0x1f, 0xef, 0xae,
    0x00, 0x7a, 0xef, 0xae, 0x00, 0xba, 0xef, 0xae, 0x00, 0xeb, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xeb, 0xef, 0xae, 0x00, 0xba, 0xef, 0xae, 0x00, 0x7a, 0xef, 0xae,
    0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xef, 0xae, 0x00, 0x1f, 0xef, 0xae, 0x00, 0xa3, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xa3, 0xef, 0xae, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xef, 0xae,
    0x00, 0x5c, 0xef, 0xae, 0x00, 0xf5, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xf5, 0xef, 0xae, 0x00, 0x5c, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xef, 0xae, 0x00, 0x66, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0x66, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xef, 0xae, 0x00, 0x5c, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0x5c, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xef, 0xae, 0x00, 0x1f, 0xef, 0xae, 0x00, 0xf5, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xf1, 0xb8, 0x3a, 0xff, 0xf2, 0xbd, 0x49, 0xff, 0xf3, 0xc3, 0x55, 0xff, 0xf3, 0xc0,
    0x4e, 0xff, 0xf2, 0xbb, 0x41, 0xff, 0xf0, 0xb1, 0x1d, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xf5, 0xef, 0xae, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xef, 0xae, 0x00, 0xa3, 0xf1, 0xba, 0x61, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf0, 0xb1,
    0x1d, 0xff, 0xf2, 0xbd, 0x47, 0xff, 0xf3, 0xc3, 0x55, 0xff, 0xf4, 0xc5, 0x58, 0xff, 0xf3, 0xc3,
    0x55, 0xff, 0xf2, 0xbf, 0x4c, 0xff, 0xf0, 0xb5, 0x30, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xa3, 0xff, 0xff, 0xff, 0x00, 0xef, 0xae,
    0x00, 0x1f, 0xef, 0xae, 0x00, 0xff, 0xf6, 0xd3, 0xaa, 0xff, 0xf9, 0xe3, 0xcb, 0xff, 0xf0, 0xb2,
    0x38, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf2, 0xc0,
    0x73, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0x1f, 0xef, 0xae,
    0x00, 0x7a, 0xef, 0xae, 0x00, 0xff, 0xf6, 0xd3, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xf4,
    0xec, 0xff, 0xf3, 0xc8, 0x8c, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf7, 0xda,
    0xb8, 0xff, 0xfc, 0xf2, 0xe7, 0xff, 0xf1, 0xba, 0x61, 0xff, 0xfb, 0xef, 0xe2, 0xff, 0xfa, 0xe9,
    0xd7, 0xff, 0xf6, 0xd7, 0xb1, 0xff, 0xf1, 0xba, 0x61, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0x7a, 0xef, 0xae,
    0x00, 0xba, 0xef, 0xae, 0x00, 0xff, 0xf3, 0xc6, 0x89, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xf7, 0xf1, 0xff, 0xfa, 0xe9, 0xd7, 0xff, 0xfe, 0xfc,
    0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf2, 0xe7, 0xff, 0xf6, 0xd7,
    0xb1, 0xff, 0xf0, 0xb3, 0x3c, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xb8, 0xef, 0xae,
    0x00, 0xea, 0xef, 0xae, 0x00, 0xff, 0xf0, 0xb2, 0x38, 0xff, 0xfe, 0xfc, 0xfa, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf8, 0xe0, 0xc4, 0xff, 0xf2, 0xc2, 0x7c, 0xff, 0xf5, 0xd0, 0xa2, 0xff, 0xfc, 0xf2,
    0xe7, 0xff, 0xf6, 0xd3, 0xaa, 0xff, 0xfc, 0xf1, 0xe6, 0xff, 0xf6, 0xd3, 0xaa, 0xff, 0xfb, 0xef,
    0xe2, 0xff, 0xf6, 0xd3, 0xaa, 0xff, 0xfb, 0xec, 0xdd, 0xff, 0xf9, 0xe3, 0xcb, 0xff, 0xf4, 0xc9,
    0x90, 0xff, 0xf6, 0xd3, 0xa9, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xe8, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf8, 0xe0, 0xc5, 0xff, 0xfd, 0xf4,
    0xec, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf3, 0xc6, 0x86, 0xff, 0xf4, 0xca, 0x91, 0xff, 0xfc, 0xf1,
    0xe5, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf8, 0xe0, 0xc5, 0xff, 0xf0, 0xb5, 0x48, 0xff, 0xf7, 0xda,
    0xb8, 0xff, 0xf2, 0xbe, 0x6f, 0xff, 0xf6, 0xd3, 0xaa, 0xff, 0xf3, 0xc5, 0x86, 0xff, 0xf1, 0xba,
    0x61, 0xff, 0xf2, 0xc2, 0x7c, 0xff, 0xf1, 0xba, 0x60, 0xff, 0xf2, 0xbe, 0x6f, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf0, 0xb6, 0x4b, 0xff, 0xfc, 0xf2,
    0xe7, 0xff, 0xf0, 0xb2, 0x38, 0xff, 0xf4, 0xcb, 0x95, 0xff, 0xf1, 0xba, 0x61, 0xff, 0xf6, 0xd7,
    0xb1, 0xff, 0xf2, 0xbe, 0x6f, 0xff, 0xf3, 0xc6, 0x86, 0xff, 0xf1, 0xba, 0x61, 0xff, 0xf2, 0xc2,
    0x7c, 0xff, 0xf1, 0xba, 0x61, 0xff, 0xf2, 0xc2, 0x7c, 0xff, 0xf6, 0xd3, 0xaa, 0xff, 0xf1, 0xbb,
    0x61, 0xff, 0xf9, 0xe2, 0xc8, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf8, 0xe1, 0xc6, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xea, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf3, 0xc6,
    0x86, 0xff, 0xfa, 0xe7, 0xd3, 0xff, 0xf3, 0xc6, 0x86, 0xff, 0xf3, 0xc6, 0x86, 0xff, 0xfd, 0xf7,
    0xf1, 0xff, 0xf6, 0xd7, 0xb1, 0xff, 0xf4, 0xc9, 0x90, 0xff, 0xf3, 0xc6, 0x86, 0xff, 0xf6, 0xd3,
    0xa9, 0xff, 0xf3, 0xc6, 0x86, 0xff, 0xf8, 0xe0, 0xc5, 0xff, 0xfa, 0xe9, 0xd7, 0xff, 0xf2, 0xc2,
    0x7c, 0xff, 0xfc, 0xf2, 0xe7, 0xff, 0xf2, 0xc2, 0x7c, 0xff, 0xf9, 0xe6, 0xd1, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xe7, 0xef, 0xae,
    0x00, 0xb9, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xf2, 0xbe, 0x6f, 0xff, 0xfd, 0xf4, 0xec, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xe6, 0xd1, 0xff, 0xf6, 0xd3,
    0xaa, 0xff, 0xfc, 0xf2, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xef, 0xe2, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xb8, 0xef, 0xae,
    0x00, 0x7a, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf5, 0xd0, 0xa2, 0xff, 0xfb, 0xec,
    0xdd, 0xff, 0xfe, 0xfc, 0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xf8,
    0xf2, 0xff, 0xf9, 0xe3, 0xcb, 0xff, 0xf2, 0xc0, 0x73, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xf4, 0xc9, 0x90, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6, 0xd7, 0xb1, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0x7a, 0xef, 0xae,
    0x00, 0x1f, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xf7, 0xda, 0xb8, 0xff, 0xfc, 0xf0, 0xe4, 0xff, 0xf0, 0xb2, 0x38, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0x1f, 0xff, 0xff,
    0xff, 0x00, 0xef, 0xae, 0x00, 0xa3, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf3, 0xc6,
    0x86, 0xff, 0xfe, 0xfc, 0xfa, 0xff, 0xf0, 0xb7, 0x50, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xa3, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xef, 0xae, 0x00, 0x1f, 0xef, 0xae, 0x00, 0xf5, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xfe, 0xfc,
    0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf4, 0xc9, 0x90, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xf5, 0xef, 0xae, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xef, 0xae, 0x00, 0x5c, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xf9, 0xe4,
    0xcd, 0xff, 0xfe, 0xfc, 0xfa, 0xff, 0xfa, 0xe9, 0xd7, 0xff, 0xf3, 0xc5, 0x85, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0x5c, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xef, 0xae, 0x00, 0x66, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0x66, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xef, 0xae,
    0x00, 0x5c, 0xef, 0xae, 0x00, 0xf5, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xf5, 0xef, 0xae, 0x00, 0x5c, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xef, 0xae, 0x00, 0x1f, 0xef, 0xae, 0x00, 0xa3, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xa3, 0xef, 0xae, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xef, 0xae, 0x00, 0x1f, 0xef, 0xae,
    0x00, 0x7a, 0xef, 0xae, 0x00, 0xb8, 0xef, 0xae, 0x00, 0xe7, 0xef, 0xae, 0x00, 0xff, 0xef, 0xae,
    0x00, 0xff, 0xef, 0xae, 0x00, 0xe6, 0xef, 0xae, 0x00, 0xb8, 0xef, 0xae, 0x00, 0x7a, 0xef, 0xae,
    0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
    0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xfe, 0x00,
    0x7f, 0x00, 0xf8, 0x00, 0x1f, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0xe0, 0x00, 0x07, 0x00, 0xc0, 0x00,
    0x03, 0x00, 0x80, 0x00, 0x01, 0x00, 0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x01, 0x00, 0x80, 0x00, 0x01, 0x00, 0xc0, 0x00, 0x03, 0x00, 0xe0, 0x00,
    0x07, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0xf8, 0x00, 0x1f, 0x00, 0xfe, 0x00, 0x7f, 0x00,
};

#define ICON_SIZE    (sizeof(icon_file))
#define EMFAT_INCR_ICON 1
#else
#define EMFAT_INCR_ICON 0
#endif

#define CMA_TIME EMFAT_ENCODE_CMA_TIME(1,1,2018, 13,0,0)
#define CMA { CMA_TIME, CMA_TIME, CMA_TIME }

static void memory_read_proc(uint8_t *dest, int size, uint32_t offset, emfat_entry_t *entry)
{
    int len;

    if (offset > entry->curr_size) {
        return;
    }

    if (offset + size > entry->curr_size) {
        len = entry->curr_size - offset;
    } else {
        len = size;
    }

    memcpy(dest, &((char *)entry->user_data)[offset], len);
}

static void bblog_read_proc(uint8_t *dest, int size, uint32_t offset, emfat_entry_t *entry)
{
    UNUSED(entry);

    flashfsReadAbs(offset, dest, size);
}

static const emfat_entry_t entriesPredefined[] =
{
    // name           dir    attr         lvl offset  size             max_size        user                time  read               write
    { "",             true,  0,           0,  0,      0,               0,              0,                  CMA,  NULL,              NULL, { 0 } },
#ifdef USE_EMFAT_AUTORUN
    { "autorun.inf",  false, ATTR_HIDDEN, 1,  0,      AUTORUN_SIZE,    AUTORUN_SIZE,   (long)autorun_file, CMA,  memory_read_proc,  NULL, { 0 } },
#endif
#ifdef USE_EMFAT_ICON
    { "icon.ico",     false, ATTR_HIDDEN, 1,  0,      ICON_SIZE,       ICON_SIZE,      (long)icon_file,    CMA,  memory_read_proc,  NULL, { 0 } },
#endif
#ifdef USE_EMFAT_README
    { "readme.txt",   false, 0,           1,  0,      README_SIZE,     1024*1024,      (long)readme_file,  CMA,  memory_read_proc,  NULL, { 0 } },
#endif
    { "EGOF_ALL.BBL", 0,     0,           1,  0,      0,               0,              0,                  CMA,  bblog_read_proc,   NULL, { 0 } },

    { "PADDING.TXT",  0,     ATTR_HIDDEN, 1,  0,      0,               0,              0,                  CMA,  NULL,              NULL, { 0 } },
};

#define PREDEFINED_ENTRY_COUNT (1 + EMFAT_INCR_AUTORUN + EMFAT_INCR_ICON + EMFAT_INCR_README)
#define APPENDED_ENTRY_COUNT 2

#define EMFAT_MAX_LOG_ENTRY 100
#define EMFAT_MAX_ENTRY (PREDEFINED_ENTRY_COUNT + EMFAT_MAX_LOG_ENTRY + APPENDED_ENTRY_COUNT)

static emfat_entry_t entries[EMFAT_MAX_ENTRY];
static char logNames[EMFAT_MAX_LOG_ENTRY][8+3];

emfat_t emfat;

static void emfat_add_log(emfat_entry_t *entry, int number, uint32_t offset, uint32_t size)
{
    tfp_sprintf(logNames[number], "EGOF_%03d.BBL", number + 1);

    entry->name = logNames[number];
    entry->level = 1;
    entry->offset = offset;
    entry->curr_size = size;
    entry->max_size = entry->curr_size;
    entry->cma_time[0] = CMA_TIME;
    entry->cma_time[1] = CMA_TIME;
    entry->cma_time[2] = CMA_TIME;
    entry->readcb = bblog_read_proc;
}

static int emfat_find_log(emfat_entry_t *entry, int maxCount)
{
    uint32_t limit  = flashfsIdentifyStartOfFreeSpace();
    uint32_t lastOffset = 0;
    uint32_t currOffset = 0;
    int fileNumber = 0;
    uint8_t buffer[18];
    int logCount = 0;

    for ( ; currOffset < limit ; currOffset += 2048) { // XXX 2048 = FREE_BLOCK_SIZE in io/flashfs.c

        flashfsReadAbs(currOffset, buffer, 18);

        if (strncmp((char *)buffer, "H Product:Blackbox", 18)) {
            continue;
        }

        if (lastOffset != currOffset) {
            emfat_add_log(entry, fileNumber, lastOffset, currOffset - lastOffset);

            ++fileNumber;
            ++logCount;
            if (fileNumber == maxCount) {
                break;
            }
            ++entry;
        }

        lastOffset = currOffset;
    }

    if (fileNumber != maxCount && lastOffset != currOffset) {
        emfat_add_log(entry, fileNumber, lastOffset, currOffset - lastOffset);
        ++logCount;
    }
    return logCount;
}

void emfat_init_files(void)
{
    emfat_entry_t *entry;
    memset(entries, 0, sizeof(entries));

    for (size_t i = 0 ; i < PREDEFINED_ENTRY_COUNT ; i++) {
        entries[i] = entriesPredefined[i];
    }

    // Detect and create entries for each individual log
    const int logCount = emfat_find_log(&entries[PREDEFINED_ENTRY_COUNT], EMFAT_MAX_LOG_ENTRY);

    int entryIndex = PREDEFINED_ENTRY_COUNT + logCount;

    if (logCount > 0) {
        // Create the all logs entry that represents all used flash space to
        // allow downloading the entire log in one file
        entries[entryIndex] = entriesPredefined[PREDEFINED_ENTRY_COUNT];
        entry = &entries[entryIndex];
        entry->curr_size = flashfsIdentifyStartOfFreeSpace();
        entry->max_size = entry->curr_size;
        ++entryIndex;
    }

    // Padding file to fill out the filesystem size to FILESYSTEM_SIZE_MB
    entries[entryIndex] = entriesPredefined[PREDEFINED_ENTRY_COUNT + 1];
    entry = &entries[entryIndex];
    // used space is doubled because of the individual files plus the single complete file
    entry->curr_size = (FILESYSTEM_SIZE_MB * 1024 * 1024) - (flashfsIdentifyStartOfFreeSpace() * 2);
    entry->max_size = entry->curr_size;

    emfat_init(&emfat, "EGOF", entries);

}
