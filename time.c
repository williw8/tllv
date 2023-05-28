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

#include <errno.h>

#include "tllv.h"


void tllv_insert_time(tllv_t *tllv,tllv_time_t *t,int *err)
{
    int chk = 0;

    if (tllv && t) {
        uint8_t *ptr ;

        tllv_alloc_value(tllv,0,&chk);
        if (0 == chk) {
            ptr = (uint8_t *) &(tllv->value);
	    *ptr++ = t->hour;
	    *ptr++ = t->minute;
	    *ptr++ = t->seconds;
	    *ptr = t->gmt_offset;
	    tllv->type = TLLV_TIME;
            tllv->len = 4;
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}

void tllv_extract_time(tllv_t *tllv,tllv_time_t *t,int *err)
{
    int chk = 0;

    if (tllv && t) {
        if (TLLV_TIME == tllv->type) {
            uint8_t *ptr = (uint8_t *) &(tllv->value);
            t->hour = *ptr++;
            t->minute = *ptr++;
            t->seconds = *ptr++;
            t->gmt_offset = *ptr++;
        } else {
            chk = TLLV_ERR_INVALID_TYPE; 
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}


