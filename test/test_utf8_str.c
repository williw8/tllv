/***************************************************************************
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

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tllv.h"
#include "test_tllv.h"

#define MAX_STATIC_STR_LEN    1024
#define LONG_STR_LEN          0x20000

static uint8_t STR1[] = {};
static uint32_t STR1_LEN = 0;
static uint8_t STR2[] = {0xc3,0x80,0x00};
static uint32_t STR2_LEN = 2;
static uint8_t STR3[] = {0xc3,0x80,0xc3,0x81,0x00};
static uint32_t STR3_LEN = 4;
static uint8_t STR4[] = {0xc3,0x80,0xc3,0x81,0xc3,0x82,0x00};
static uint32_t STR4_LEN = 6;
static uint8_t STR5[] = {0xc3,0x80,0xc3,0x81,0xc3,0x82,0xc3,0x83,0xc3,0x84,0xc3,0x85,0xc3,0x86,0xc3,0x87,0x00};
static uint32_t STR5_LEN = 16;
static uint8_t STR6[] = {0xc3,0x80,0xc3,0x81,0xc3,0x82,0xc3,0x83,0xc3,0x84,0xc3,0x85,0xc3,0x86,0xc3,0x87,
                         0xc3,0x88,0xc3,0x89,0x00};
static uint32_t STR6_LEN = 20;
static uint8_t STR7[] = {0xc3,0x80,0xc3,0x81,0xc3,0x82,0xc3,0x83,0xc3,0x84,0xc3,0x85,0xc3,0x86,0xc3,0x87,
                         0xc3,0x88,0xc3,0x89,0xc3,0x8a,0xc3,0x8b,0xc3,0x8c,0xc3,0x8d,0xc3,0x8e,0xc3,0x8f,0x00};
static uint32_t STR7_LEN = 32;

int test_utf8_str(test_node_t *rec)
{
    int rv = 0;
    int err;
    int line;
    int line_number_idx = 0;
    uint32_t len;
    uint8_t str[MAX_STATIC_STR_LEN];
    tllv_t *tllv;
    uint8_t *long_str_base;
    uint8_t *long_str_chk;

    if (!rec) {
        rv = EINVAL;
        goto out;
    }
    test_node_set_name(rec,__func__);

    tllv = create_tllv();
    if (tllv) {
        // STR1
        tllv_insert_utf8_string(tllv,STR1,STR1_LEN,&err);
        if (err) {
            rv = err;
            goto out;
        }
        len = tllv->len;
        tllv_extract_utf8_string(tllv,str,&len,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
	str[len] = '\0';
        if (0 == memcmp(STR1,str,len)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR2
        tllv_insert_utf8_string(tllv,STR2,STR2_LEN,&err);
        if (err) {
            rv = err;
            goto out;
        }
        len = tllv->len;
        tllv_extract_utf8_string(tllv,str,&len,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
	str[len] = '\0';
        if (0 == memcmp(STR2,str,len)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR3
        tllv_insert_utf8_string(tllv,STR3,STR3_LEN,&err);
        if (err) {
            rv = err;
            goto out;
        }
        len = tllv->len;
        tllv_extract_utf8_string(tllv,str,&len,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
	str[len] = '\0';
        if (0 == memcmp(STR3,str,len)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR4
        tllv_insert_utf8_string(tllv,STR4,STR4_LEN,&err);
        if (err) {
            rv = err;
            goto out;
        }
        len = tllv->len;
        tllv_extract_utf8_string(tllv,str,&len,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
	str[len] = '\0';
        if (0 == memcmp(STR4,str,len)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR5
        tllv_insert_utf8_string(tllv,STR5,STR5_LEN,&err);
        if (err) {
            rv = err;
            goto out;
        }
        len = tllv->len;
        tllv_extract_utf8_string(tllv,str,&len,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
	str[len] = '\0';
        if (0 == memcmp(STR5,str,len)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR6
        tllv_insert_utf8_string(tllv,STR6,STR6_LEN,&err);
        if (err) {
            rv = err;
            goto out;
        }
        len = tllv->len;
        tllv_extract_utf8_string(tllv,str,&len,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
	str[len] = '\0';
        if (0 == memcmp(STR6,str,len)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

        // STR7
        tllv_insert_utf8_string(tllv,STR7,STR7_LEN,&err);
        if (err) {
            rv = err;
            goto out;
        }
        len = tllv->len;
        tllv_extract_utf8_string(tllv,str,&len,&err);
        line = __LINE__ + 1;
        if (err) {
            rv = err;
            goto out;
	}
	str[len] = '\0';
        if (0 == memcmp(STR7,str,len)) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }

	// Long string
        long_str_base = calloc(1,LONG_STR_LEN+1);
        if (long_str_base) {
            long_str_chk = calloc(1,LONG_STR_LEN+1);
            if (long_str_chk) {
                int i;
                for (i=0;i<LONG_STR_LEN;i++) {
                    long_str_base[i] = 'a';
                }
                long_str_base[i] = '\0';
                tllv_insert_utf8_string(tllv,(uint8_t *) long_str_base,LONG_STR_LEN,&err);
                if (err) {
                    rv = err;
                    goto out;
                }
                len = LONG_STR_LEN;
                tllv_extract_utf8_string(tllv,(uint8_t *) long_str_chk,&len,&err);
                line = __LINE__ + 1;
                if (0 == memcmp(long_str_base,long_str_chk,len)) {
                    ++(rec->passed_test_count);
                } else {
                    ++(rec->failed_test_count);
                   if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                       rec->failed_test_lines[line_number_idx++] = line;
                   }
                }
                free(long_str_chk);
            }
            free(long_str_base);
        }

        destroy_tllv(tllv);
    } else {
        rv = ENOMEM; 
    }
out:
    return rv;
}


