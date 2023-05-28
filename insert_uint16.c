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


void tllv_insert_uint16(tllv_t *tllv,uint16_t v,int *err)
{
    int chk = 0;

    if (tllv) {
        uint8_t *ptr ;
        tllv_alloc_value(tllv,0,&chk);
	if (0 == chk) {
            ptr = (uint8_t *) &(tllv->value);
	    *ptr++ = (uint8_t) ((v & 0xff00) >> 8);
	    *ptr = (uint8_t) (v & 0x00ff);
	    tllv->type = TLLV_UINT16_BE;
            tllv->len = 2;	
            tllv_set_free_value_flag(tllv,0);
        }
    } else {
        chk = EINVAL;        
    }
    if (err) {
        *err = chk;
    }
}


