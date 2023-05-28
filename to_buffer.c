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


void tllv_to_buffer(tllv_t *tllv,uint8_t *buf,uint32_t buflen,int *err)
{
    int rv = 0;
    uint8_t *cptr;
    if (tllv && buf) {
        int buf_idx = 0;
        int tllv_idx = 0;
        if (buflen >= (tllv->len + 4)) {
            buf[buf_idx++] = ((tllv->type & 0xff00) >> 8);
            buf[buf_idx++] = (tllv->type & 0x00ff);
            buf[buf_idx++] = ((tllv->len & 0xff00) >> 8);
            buf[buf_idx++] = (tllv->len & 0x00ff);
            cptr = (uint8_t *) tllv->value;
	    for (tllv_idx=0;tllv_idx<tllv->len;tllv_idx++) {
                buf[buf_idx++] = cptr[tllv_idx];
	    }
	} else {
            rv = ENOBUFS;
        }
    } else {
        rv = EINVAL;
    }
    if (err) {
        *err = rv;
    }
}


