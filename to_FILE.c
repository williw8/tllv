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


void tllv_to_FILE(tllv_t *tllv,FILE *fptr,int *err)
{
    int chk;
    int error = 0;
    if (tllv && fptr) {
        uint8_t buf[4];
        int buf_idx = 0;
        buf[buf_idx++] = ((tllv->type & 0xff00) >> 8);
        buf[buf_idx++] = (tllv->type & 0x00ff);
        buf[buf_idx++] = ((tllv->len & 0xff00) >> 8);
        buf[buf_idx++] = (tllv->len & 0x00ff);
	chk = fwrite(buf,1,sizeof(buf),fptr);
	if (sizeof(buf) == chk) {
	    if (tllv->value && (tllv->len > 0)) {
	        chk = fwrite(tllv->value,1,tllv->len,fptr);
                if (chk != tllv->len) {
		    error = errno;
                }
	    }
	} else {
	    error = errno;
	}
    } else {
        error = EINVAL;
    }
    if (err) {
        *err = error;
    }
}


