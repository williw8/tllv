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


void tllv_insert_date(tllv_t *tllv,tllv_date_t *d,int *err)
{
    int chk = 0;

    if (tllv && d) {
        uint8_t *ptr ;

        tllv_alloc_value(tllv,0,&chk);
        if (0 == chk) {
            ptr = (uint8_t *) &(tllv->value);
	    *ptr++ = (uint8_t) ((d->year & 0xff00) >> 8);
	    *ptr++ = (uint8_t) (d->year & 0x00ff);
	    *ptr++ = (uint8_t) (d->month & 0xff);
	    *ptr = (uint8_t) (d->day & 0xff);
	    tllv->type = TLLV_DATE;
            tllv->len = 4;
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}

void tllv_extract_date(tllv_t *tllv,tllv_date_t *d,int *err)
{
    int chk = 0;

    if (tllv && d) {
        if (TLLV_DATE == tllv->type) {
            uint8_t *ptr = (uint8_t *) &(tllv->value);
            d->year = (uint16_t ) ((*ptr++) << 8);
            d->year |= (uint16_t) *ptr++;
            d->month = (uint8_t) *ptr++;
            d->day = (uint8_t) *ptr++;
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


