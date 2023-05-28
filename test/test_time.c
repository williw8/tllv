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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tllv.h"
#include "test_tllv.h"


int test_time(test_node_t *rec)
{
    int rv = 0;
    int err;
    int line;
    int line_number_idx = 0;
    tllv_t *tllv;

    if (!rec) {
        rv = EINVAL;
        goto out;
    }
    test_node_set_name(rec,__func__);

    tllv = create_tllv();
    if (tllv) {
        time_t tt;
	struct tm ttm;
        tllv_time_t iv;
        tllv_time_t ev;

        memset(&ev,0,sizeof(ev));
        memset(&iv,0,sizeof(iv));
	tt = time(NULL);
        localtime_r(&tt,&ttm);
	iv.hour = ttm.tm_hour;
	iv.minute = ttm.tm_min;
	iv.seconds = ttm.tm_sec;
        tllv_insert_time(tllv,&iv,&err);
        if (err) {
            rv = err;
            goto out;
        }
        tllv_extract_time(tllv,&ev,&err);
        line = __LINE__ + 1;
        if (iv.hour == ev.hour) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }
        line = __LINE__ + 1;
        if (iv.minute == ev.minute) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }
        line = __LINE__ + 1;
        if (iv.seconds == ev.seconds) {
            ++(rec->passed_test_count);
        } else {
            ++(rec->failed_test_count);
            if (line_number_idx < MAX_REPORTED_TEST_LINES) {
                rec->failed_test_lines[line_number_idx++] = line;
            }
        }
        destroy_tllv(tllv);
    } else {
        rv = ENOMEM; 
    }
out:
    return rv;
}


