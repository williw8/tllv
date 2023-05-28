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



int tllv_should_free_value(tllv_t *tllv)
{
    int rv = 0;
    if (tllv) {
        rv = (tllv->flags &  FLAG_FREE_VALUE);
    }
    return rv;
}

int tllv_should_free_as_list(tllv_t *tllv)
{
    int rv = 0;
    if (tllv) {
        rv = (tllv->flags &  FLAG_FREE_AS_LIST);
    }
    return rv;
}

int tllv_set_free_value_flag(tllv_t *tllv,uint32_t v)
{
    int rv = 0;
    if (tllv) {
        if (v) {
            tllv->flags |= FLAG_FREE_VALUE;
        } else {
            tllv->flags &= ~FLAG_FREE_VALUE;
        }
    }
    return rv;
}

int tllv_set_free_as_list_flags(tllv_t *tllv,uint32_t v)
{
    int rv = 0;
    if (tllv) {
        if (v) {
            tllv->flags |= FLAG_FREE_AS_LIST;
        } else {
            tllv->flags &= ~FLAG_FREE_AS_LIST;
        }
    }
    return rv;
}

