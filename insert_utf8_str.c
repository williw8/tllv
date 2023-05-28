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

void tllv_insert_utf8_string(tllv_t *tllv,const uint8_t *str,uint32_t len,int *err)
{
    int chk = 0;
    if (tllv && str) {
        uint32_t i;
        uint8_t *cptr;
        tllv_t *tail;
        tllv_t *new_tllv;
        if (len < 0x00010000) {
            tllv_alloc_value(tllv,len,&chk);
            if (0 == chk) {
                cptr = (uint8_t *) tllv->value;
                for (i=0;i<len;i++) {
                    cptr[i] = *str++;
                }
                tllv->type = TLLV_UTF8_STRING;
                tllv->next = NULL;
            } else {
                goto out;
            }
        } else {
            uint32_t chunk_len = 0x0000ffff;
            tllv_alloc_value(tllv,chunk_len,&chk);
            if (0 == chk) {
                uint32_t i;
                cptr = (uint8_t *) tllv->value;
                for (i=0;i<chunk_len;i++) {
                    cptr[i] = (uint8_t) *str++;
                }
                tllv->type = TLLV_UTF8_STRING_FIRST;
                tail = tllv;
            } else {
                goto out;
            }
            len -= chunk_len;
            while (len >= 0x00010000) {
                new_tllv = create_tllv();
                if (new_tllv) {
                    tllv_alloc_value(new_tllv,chunk_len,&chk);
                    if (0 == chk) {
                        uint32_t i;
                        cptr = (uint8_t *) new_tllv->value;
                        for (i=0;i<chunk_len;i++) {
                            cptr[i] = (uint8_t) *str++;
                        }
                    } else {
                        goto out;
                    }
                    len -= chunk_len;
                    if (0 == len) {
                        new_tllv->type = TLLV_UTF8_STRING_LAST;
                    } else {
                        new_tllv->type = TLLV_UTF8_STRING;
                    }
                    tail->next = new_tllv;
                    tail = new_tllv;
		} else {
                    chk = ENOMEM;
                    goto destroy_chain;
                }
            }
            if (len > 0) {
                uint32_t chunk_len = len;
                new_tllv = create_tllv();
                if (new_tllv) {
                    tllv_alloc_value(new_tllv,chunk_len,&chk);
                    if (0 == chk) {
                        uint32_t i;
                        cptr = (uint8_t *) new_tllv->value;
                        for (i=0;i<chunk_len;i++) {
                            cptr[i] = (uint8_t) *str++;
                        }
                        new_tllv->type = TLLV_UTF8_STRING_LAST;
                        tail->next = new_tllv;
                    }
                } else {
                    chk = ENOMEM;
                    goto destroy_chain;
                }
            }
        }
        goto out;
    } else {
        chk = EINVAL;
    }
destroy_chain:
    destroy_tllv_list(tllv->next);
out:
    if (err) {
        *err = chk;
    }
}

