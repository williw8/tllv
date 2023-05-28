/***************************************************************************
 *  TLLV is a C-language library that provides access to 
 *  TLLV (type, label, length, value) structures.
 *  Copyright (C) 2023 Winslow Williams 
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef _TLLV_20230115
#define _TLLV_20230115

#include <stdio.h>
#include <stdint.h>

#define FLAG_FREE_VALUE                 0x8000
#define FLAG_FREE_AS_LIST               0x4000

#define TLLV_NULL                        0x0000 /* TLV with NULL value (length = 0) */
#define TLLV_DATA                        0x0001 /* Data with no specific type */
#define TLLV_INT8                        0x0002 /* Signed one-byte integer */
#define TLLV_UINT8                       0x0003 /* Unsigned one-byte integer */
#define TLLV_INT8_ARRAY                  0x0004 /* Array of 8-bit signed integers */
#define TLLV_INT8_ARRAY_FIRST            0x0005 /* Array of 8-bit signed integers, first in a series */
#define TLLV_INT8_ARRAY_LAST             0x0006 /* Array of 8-bit signed integers, last in a series */
#define TLLV_UINT8_ARRAY                 0x0007 /* Array of 8-bit unsigned integers */
#define TLLV_UINT8_ARRAY_FIRST           0x0008 /* Array of 8-bit unsigned integers, first in a series */
#define TLLV_UINT8_ARRAY_LAST            0x0009 /* Array of 8-bit unsigned integers, last in a series */

#define TLLV_INT16_BE                    0x000a /* Signed 16-bit big-endian integer */
#define TLLV_UINT16_BE                   0x000b /* Unsigned 16-bit big-endian integer */
#define TLLV_INT16_BE_ARRAY              0x000c /* Array of 16-bit big-endian signed integers */
#define TLLV_INT16_BE_ARRAY_FIRST        0x000d /* Array of 16-bit big-endian signed integers, first in a series */
#define TLLV_INT16_BE_ARRAY_LAST         0x000e /* Array of 16-bit big-endian signed integers, last in a series */
#define TLLV_UINT16_BE_ARRAY             0x000f /* Array of 16-bit big-endian unsigned integers */
#define TLLV_UINT16_BE_ARRAY_FIRST       0x0010 /* Array of 16-bit big-endian unsigned integers, first in a series */
#define TLLV_UINT16_BE_ARRAY_LAST        0x0011 /* Array of 16-bit big-endian unsigned integers, last in a series */

#define TLLV_INT16_LE                    0x0012 /* Signed 16-bit little-endian integer */
#define TLLV_UINT16_LE                   0x0013 /* Unsigned 16-bit little-endian integer */
#define TLLV_INT16_LE_ARRAY              0x0014 /* Array of 16-bit little-endian signed integers */
#define TLLV_INT16_LE_ARRAY_FIRST        0x0015 /* Array of 16-bit little-endian signed integers, first in a series */
#define TLLV_INT16_LE_ARRAY_LAST         0x0016 /* Array of 16-bit little-endian signed integers, last in a series */
#define TLLV_UINT16_LE_ARRAY             0x0017 /* Array of 16-bit little-endian unsigned integers */
#define TLLV_UINT16_LE_ARRAY_FIRST       0x0018 /* Array of 16-bit little-endian unsigned integers, first in a series */
#define TLLV_UINT16_LE_ARRAY_LAST        0x0019 /* Array of 16-bit little-endian unsigned integers, last in a series */

#define TLLV_INT32_BE                    0x001a /* Signed 32-bit big-endian integer */
#define TLLV_UINT32_BE                   0x001b /* Unsigned 32-bit big-endian integer */
#define TLLV_INT32_BE_ARRAY              0x001c /* Array of 32-bit big-endian signed integers */
#define TLLV_INT32_BE_ARRAY_FIRST        0x001d /* Array of 32-bit big-endian signed integers, first in a series */
#define TLLV_INT32_BE_ARRAY_LAST         0x001e /* Array of 32-bit big-endian signed integers, last in a series */
#define TLLV_UINT32_BE_ARRAY             0x001f /* Array of 32-bit big-endian unsigned integers */
#define TLLV_UINT32_BE_ARRAY_FIRST       0x0020 /* Array of 32-bit big-endian unsigned integers, first in a series */
#define TLLV_UINT32_BE_ARRAY_LAST        0x0021 /* Array of 32-bit big-endian unsigned integers, last in a series */

#define TLLV_INT32_LE                    0x0022 /* Signed 32-bit little-endian integer */
#define TLLV_UINT32_LE                   0x0023 /* Unsigned 32-bit little-endian integer */
#define TLLV_INT32_LE_ARRAY              0x0024 /* Array of 32-bit little-endian signed integers */
#define TLLV_INT32_LE_ARRAY_FIRST        0x0025 /* Array of 32-bit little-endian signed integers, first in a series */
#define TLLV_INT32_LE_ARRAY_LAST         0x0026 /* Array of 32-bit little-endian signed integers, last in a series */
#define TLLV_UINT32_LE_ARRAY             0x0027 /* Array of 32-bit little-endian unsigned integers */
#define TLLV_UINT32_LE_ARRAY_FIRST       0x0028 /* Array of 32-bit little-endian unsigned integers, first in a series */
#define TLLV_UINT32_LE_ARRAY_LAST        0x0029 /* Array of 32-bit little-endian unsigned integers, last in a series */

#define TLLV_CSTR_CHAR                   0x002a /* Single ASCII character */
#define TLLV_CSTR_STRING                 0x002b /* Null-terminated c-style ASCII character string */
#define TLLV_CSTR_STRING_FIRST           0x002c /* Null-terminated c-style ASCII character string, first in a series */
#define TLLV_CSTR_STRING_LAST            0x002d /* Null-terminated c-style ASCII character string, last in a series */

#define TLLV_UTF8_CHAR                   0x002e /* Single UTF-8 character */
#define TLLV_UTF8_STRING                 0x002f /* UTF-8 character string (not terminated) */
#define TLLV_UTF8_STRING_FIRST           0x0030 /* UTF-8 character string, first in a series (not terminated) */
#define TLLV_UTF8_STRING_LAST            0x0031 /* UTF-8 character string, last in a series (not terminated) */

#define TLLV_UTF16_BE_CHAR               0x0032 /* Single big-endian UTF-16 character */
#define TLLV_UTF16_BE_STRING             0x0033 /* Big-endian UTF-16 character string (not terminated) */
#define TLLV_UTF16_BE_STRING_FIRST       0x0034 /* Big-endian UTF-16 character string, first in a series (not terminated) */
#define TLLV_UTF16_BE_STRING_LAST        0x0035 /* Big-endian UTF-16 character string, last in a series (not terminated) */
#define TLLV_UTF16_LE_CHAR               0x0036 /* Single little-endian UTF-16 character */
#define TLLV_UTF16_LE_STRING             0x0037 /* Little-endian UTF-16 character string (not terminated) */
#define TLLV_UTF16_LE_STRING_FIRST       0x0038 /* Little-endian UTF-16 character string, first in a series (not terminated) */
#define TLLV_UTF16_LE_STRING_LAST        0x0039 /* Little-endian UTF-16 character string, last in a series (not terminated) */

#define TLLV_UTF32_BE_CHAR               0x003A /* Single big-endian UTF-32 character */
#define TLLV_UTF32_BE_STRING             0x003B /* Big-endian UTF-32 character string (not terminated) */
#define TLLV_UTF32_BE_STRING_FIRST       0x004C /* Big-endian UTF-32 character string, first in a series (not terminated) */
#define TLLV_UTF32_BE_STRING_LAST        0x004D /* Big-endian UTF-32 character string, last in a series (not terminated) */
#define TLLV_UTF32_LE_CHAR               0x003E /* Single littlen-endian UTF-32 character */
#define TLLV_UTF32_LE_STRING             0x003F /* Little-endian UTF-32 character string (not terminated) */
#define TLLV_UTF32_LE_STRING_FIRST       0x0040 /* Little-endian UTF-32 character string, first in a series (not terminated) */
#define TLLV_UTF32_LE_STRING_LAST        0x0041 /* Little-endian UTF-32 character string, last in a series (not terminated) */
#define TLLV_LIST                        0x0042 /* Generic list of TLV objects */
#define TLLV_LIST_FIRT                   0x0043 /* Generic list of TLV objects, first in series */
#define TLLV_LIST_LAST                   0x0044 /* Generic list of TLV objects, last in series */

#define TLLV_UUID                        0x0045 /* 16-byte big-endian UUID */
#define TLLV_DATE                        0x0046 /* 32-bit big-endian integer containing YYYYMMDD formatted date */
#define TLLV_TIME                        0x0047 /* 16-bit big-endian integer containing HMS (hour, minute, second) formatted time */
#define TLLV_DATETIME                    0x0048 /* 32-bit big-endian integer formatted as above-described date and time */
#define TLLV_GPS_COORDINATES             0x0049 /* GPS coordianates (format?) */ 

#define TLLV_APP_SPECIFIC_START          0x7000 /* Start of reserved application-specific values */
#define TLLV_APP_SPECIFIC_END            0x7FFF /* End of reserved application-specific values */

#define TLLV_ERR_BASE                    17000
#define TLLV_ERR_INVALID_TYPE    TLLV_ERR_BASE + 1
/* Be sure to update "LAST_ERROR" when adding new error codes */
#define TLLV_ERR_LAST_ERROR      TLLV_ERR_INVALID_TYPE

#define UUID_LEN                        16

typedef struct tllv
{
    struct tllv *next;
    void  *value;
    uint16_t type;
    uint16_t label;
    uint16_t flags;
    uint16_t len;
} tllv_t;

tllv_t *create_tllv(void);
int init_tllv(tllv_t *v);
void destroy_tllv(tllv_t *tllv);
void destroy_tllv_list(tllv_t *head);

typedef struct tllv_date
{
    uint16_t year;
    uint8_t month;       // 1 = January, 2 = February etc.
    uint8_t day;         // 1 - 31
} tllv_date_t;

typedef struct tllv_time
{
    uint8_t hour;
    uint8_t minute;
    uint8_t seconds;
    int8_t gmt_offset;
} tllv_time_t;

typedef struct tllv_datetime
{
    tllv_date_t date;
    tllv_time_t time;
} tllv_datetime_t;

typedef struct tllv_uuid
{
    uint8_t d[UUID_LEN]; 
} tllv_uuid_t;

void tllv_alloc_value(tllv_t *tllv,uint32_t size,int *err);
void tllv_free_value(tllv_t *tllv,int *err);
uint32_t tllv_size(tllv_t *tllv);
int tllv_should_free_value(tllv_t *tllv);
int tllv_should_free_as_list(tllv_t *tllv);
int tllv_set_free_value_flag(tllv_t *tllv,uint32_t v);
int tllv_set_free_value_flag(tllv_t *tllv,uint32_t v);
void tllv_to_buffer(tllv_t *tllv,uint8_t *buf,uint32_t buflen,int *err);
tllv_t *tllv_from_buffer(uint8_t *buf,uint32_t buflen,int *err);
void tllv_to_FILE(tllv_t *tllv,FILE *fptr,int *err);
tllv_t *tllv_from_FILE(FILE *fptr,int *err);

void tllv_insert_int8(tllv_t *tllv,int8_t v,int *err);
int8_t tllv_extract_int8(tllv_t *tllv,int *err);
void tllv_insert_uint8(tllv_t *tllv,uint8_t v,int *err);
uint8_t tllv_extract_uint8(tllv_t *tllv,int *err);

void tllv_insert_int16(tllv_t *tllv,int16_t v,int *err);
int16_t tllv_extract_int16(tllv_t *tllv,int *err);
void tllv_insert_uint16(tllv_t *tllv,uint16_t v,int *err);
uint16_t tllv_extract_uint16(tllv_t *tllv,int *err);

void tllv_insert_int32(tllv_t *tllv,int32_t v,int *err);
int32_t tllv_extract_int32(tllv_t *tllv,int *err);
void tllv_insert_uint32(tllv_t *tllv,uint32_t v,int *err);
uint32_t tllv_extract_uint32(tllv_t *tllv,int *err);

void tllv_insert_int64(tllv_t *tllv,int64_t v,int *err);
int64_t tllv_extract_int64(tllv_t *tllv,int *err);
void tllv_insert_uint64(tllv_t *tllv,uint64_t v,int *err);
uint64_t tllv_extract_uint64(tllv_t *tllv,int *err);

void tllv_insert_cstr_string(tllv_t *tllv,const char *str,int *err);
void tllv_extract_cstr_string(tllv_t *tllv,char *str,uint32_t strlen,int *err);

void tllv_insert_utf8_string(tllv_t *tllv,const uint8_t *str,uint32_t len,int *err);
void tllv_extract_utf8_string(tllv_t *tllv,uint8_t *str,uint32_t *strlen,int *err);

void tllv_insert_date(tllv_t *tllv,tllv_date_t *d,int *err);
void tllv_extract_date(tllv_t *tllv,tllv_date_t *d,int *err);
void tllv_insert_time(tllv_t *tllv,tllv_time_t *t,int *err);
void tllv_extract_time(tllv_t *tllv,tllv_time_t *t,int *err);
void tllv_insert_datetime(tllv_t *tllv,tllv_datetime_t *dt,int *err);
void tllv_extract_datetime(tllv_t *tllv,tllv_datetime_t *dt,int *err);

void tllv_insert_uuid_string(tllv_t *tllv,const char *str,int *err);
void tllv_extract_uuid_string(tllv_t *tllv,char *str,uint32_t strlen,int *err);

int tllv_is_valid_error_code(int code);
const char *tllv_get_error_string(int code);

#endif /* _TLLV_20230115 */




