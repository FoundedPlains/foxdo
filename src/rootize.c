/*
foxdo - suckless sudo/doas
Copyright (C) <year>  <name of author>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <unistd.h>
#include <grp.h>

#include "rootize.h"

short rootize() {
    int ret = setuid(0);
    if (ret)
        return 1;
    ret = setgid(0);
    if (ret)
        return 1;
    ret = seteuid(0);
    if (ret)
        return 1;
    
    gid_t groups = { 0 };
    ret = setgroups(1, &groups);
    if (ret)
        return 1;
        
    return 0;
}