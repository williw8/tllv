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


void tllv_alloc_value(tllv_t *tllv,uint32_t size,int *err)
{
    int chk = 0;
    if (tllv) {
        tllv_free_value(tllv,&chk);
        if ((0 == chk) && (size > 0)) {
            tllv->value = calloc(1,size);
            if (!(tllv->value)) {
                chk = ENOMEM;
            }
            tllv->len = size;
        } else {
            tllv->len = 0;
        }
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}
