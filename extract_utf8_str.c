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
#include <errno.h>
#include <string.h>

#include "tllv.h"

void tllv_extract_utf8_string(tllv_t *tllv,uint8_t *str,uint32_t *len,int *err)
{
    uint32_t i;
    int chk = 0;
    uint32_t total_len = 0;

    if (tllv && str && len) {
        uint32_t slen = *len;
	uint8_t *cptr;

	if (slen > 0) {
            if ((TLLV_UTF8_STRING == tllv->type) && (slen >= (tllv->len))) {
	        cptr = (uint8_t *) tllv->value;
                if ((tllv->len > 0) && cptr) {
                    for (i=0;i<(tllv->len+1);i++) {
	                str[i] = cptr[i];
	            }
                } else {
                    chk = EINVAL;
                }
                total_len = tllv->len;
	    } else if (TLLV_UTF8_STRING_FIRST == tllv->type) {
                tllv_t *ptr = tllv;
                while (ptr) {
                    if (NULL == ptr->next) {
                        if (TLLV_UTF8_STRING_LAST != ptr->type) {
                            chk = EINVAL;
                            goto out;
                        }
		    } else if (total_len > 0) {
                        if (TLLV_UTF8_STRING != ptr->type) {
                            chk = EINVAL;
                            goto out;
                        }
                    }
                    total_len += ptr->len;
                    ptr = ptr->next;
                }
                if (slen >= (total_len)) {
                    uint32_t sidx = 0;
                    ptr = tllv;
                    while (ptr) {
	                cptr = (uint8_t *) ptr->value;
                        if ((ptr->len > 0) && cptr) {
                            for (i=0;i<ptr->len;i++,sidx++) {
	                       str[sidx] = cptr[i];
	                    }
                        } else {
                            chk = EINVAL;
                            break;
                        }
                        ptr = ptr->next;
                    }
                    str[sidx] = '\0';
                } else {
                    chk = ENOBUFS;
                    goto out;
                }
            } else {
                chk = TLLV_ERR_INVALID_TYPE;
            }
            *len = total_len;
	}
    } else {
        chk = EINVAL;
    }
out:
    if (err) {
        *err = chk;
    }
}




