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


tllv_t *create_tllv(void)
{
    tllv_t *rv = calloc(1,sizeof(tllv_t));
    return rv;
}

void tllv_free_value(tllv_t *tllv,int *err)
{
    int chk = 0;
    if (tllv) {
        if (tllv->value && tllv_should_free_value(tllv)) {
            free(tllv->value);
	}
        tllv->value = NULL;
        tllv->len = 0;
	tllv->type = TLLV_NULL;
    } else {
        chk = EINVAL;
    }
    if (err) {
        *err = chk;
    }
}

/* FIXME: For lists, should destroy_tllv delete all the TLLVs in the list? */
void destroy_tllv(tllv_t *tllv)
{
    if (tllv) {
        tllv_free_value(tllv,NULL);
        free(tllv);
    }
}

void destroy_tllv_list(tllv_t *head)
{
    tllv_t *kill;
    while (head) {
        kill = head;
        head = head->next;
        destroy_tllv(kill);
    }
}
