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

void tllv_extract_cstr_string(tllv_t *tllv,char *str,uint32_t len,int *err)
{
    uint32_t i;
    int chk = 0;
    char *cptr;
    if (tllv && str) {
        if ((TLLV_CSTR_STRING == tllv->type) && (len >= (tllv->len+1))) {
            cptr = (char *) tllv->value;
	    if ((tllv->len > 0) && cptr) {
                for (i=0;i<(tllv->len+1);i++) {
	            str[i] = cptr[i];
	        }
	    } else {
                chk = EINVAL;
	    }
	} else if (TLLV_CSTR_STRING_FIRST == tllv->type) {
            uint32_t total_len = 0;
            tllv_t *ptr = tllv;
            while (ptr) {
                if (NULL == ptr->next) {
                    if (TLLV_CSTR_STRING_LAST != ptr->type) {
                        chk = EINVAL;
                        goto out;
                    }
		} else if (total_len > 0) {
                    if (TLLV_CSTR_STRING != ptr->type) {
                        chk = EINVAL;
                        goto out;
                    }
                }
                total_len += ptr->len;
                ptr = ptr->next;
            }
            if (len >= (total_len)) {
                uint32_t sidx = 0;
                ptr = tllv;
                while (ptr) {
                    cptr = (char *) ptr->value;
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
    } else {
        chk = EINVAL;
    }
out:
    if (err) {
        *err = chk;
    }
}




