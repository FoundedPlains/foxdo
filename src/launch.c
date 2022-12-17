/*
foxdo - suckless sudo/doas
Copyright (C) 2022 Ján Gajdoš

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

#include <stdlib.h>
#include <unistd.h>

#include "launch.h"

short launchWithoutArgs(char *prog) {
    char *args[] = { NULL };
    setenv("HOME", "/root", 1);
    setenv("LOGNAME", "root", 1);
    return execvpe(prog, args, __environ);
}

short launchWithArgs(char *prog, char **args) {
    setenv("HOME", "/root", 1);
    setenv("LOGNAME", "root", 1);
    return execvpe(prog, args, __environ);
}