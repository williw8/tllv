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



int8_t tllv_extract_int8(tllv_t *tllv,int *err)
{
    int8_t rv = 0;
    int error = 0;

    if (tllv) {
        if (TLLV_INT8 == tllv->type) {
            uint8_t *ptr = (uint8_t *) &(tllv->value);
            rv = (int8_t) *ptr;
        } else {
            error = TLLV_ERR_INVALID_TYPE; 
        }
    } else {
        error = EINVAL;
    }
    if (err) {
        *err = error;
    }
    return rv;
}
