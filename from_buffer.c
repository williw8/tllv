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
#include <stdlib.h>
#include "tllv.h"



tllv_t *tllv_from_buffer(uint8_t *buf,uint32_t buflen,int *err)
{
    tllv_t *rv = NULL;
    int chk = 0;
    int tllv_idx = 0;
    int buf_idx = 0;
    uint32_t typ;
    uint32_t len;

    if (buflen < 4) {
        chk = EINVAL;
        goto set_error;
    }

    typ = (buf[buf_idx++] << 8);
    typ |= buf[buf_idx++];

    len = (buf[buf_idx++] << 8);
    len |= buf[buf_idx++];

    if (buflen < (len+4)) {
        chk = EINVAL;
        goto set_error;
    }

    rv = create_tllv();
    if (rv) {
        tllv_alloc_value(rv,len,&chk);
        if (0 == chk) {
            uint8_t *cptr = (uint8_t *) rv->value;
            rv->type = typ;
            rv->len = len;
            for (tllv_idx=0;tllv_idx<len;tllv_idx++) {
                cptr[tllv_idx] = buf[buf_idx++];
	    }
	}
    } else {
        chk = ENOMEM;
    }

set_error:
    if (err) {
        *err = chk;
    }
    return rv;
}



