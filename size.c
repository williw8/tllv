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

#include "tllv.h"


/* Returns the number of bytes needed to represent this TLLV on disk or on-the-wire */
uint32_t tllv_size(tllv_t *tllv)
{
    uint32_t rv = 0;
    if (tllv) {
        if (TLLV_LIST == tllv->type && tllv->value) {
            tllv_t *ptr = (tllv_t *) tllv->value;
            while (ptr) {
                rv += tllv_size(ptr);
                ptr = ptr->next;
            }
        } else {
            rv = tllv->len + 8;
        }
    }
    return rv;
}


