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

#include "foxstd.h"
#include "src/rootize.h"
#include "src/launch.h"
#include "src/timeout.h"
#include "src/config_parser.h"
#include "src/check.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc == 1) {
        printf("foxdo [PROG] [ARGS]\n");
        return EINVAL;
    }

    FILE *conf = fopen("/etc/foxdo.foxconfig", "r");

    if (!conf) {
        printf("/etc/foxdo.foxconfig doesn't exist!\n");
        return ENOENT;
    }

    Config config = parseConfig();

    short has_group = check_groups(config);
    short has_user = check_user(config);

    char *login = getenv("USER");  

    if (!(has_group || has_user)) {
        printf("You are not allowed to use foxdo!\n");
        return EACCES;
    }

    short result = check_self(login, time(NULL));

    if (argc == 2) {
        if (result)
            printf(prompt, login);

        if (result && !FoxAuth_checkPassword(login, getpass(""))) {
            if (!geteuid())
                rootize();
                
            if (result)
                register_self(login, time(NULL) + config.t.seconds + (config.t.minutes * 60) + (config.t.hours * 60 * 60));

            launchWithoutArgs(argv[1]);
        } else {
            if (!result) {
                if (!geteuid())
                    rootize();
                launchWithoutArgs(argv[1]);
            } else {
                printf(wrong);
            }
        }
        return 0;
    }

    char *args[argc - 1];

    for (int i = 1; i < argc; i++) {
        args[i - 1] = argv[i];
    }

    args[argc - 1] = NULL;

    if (result)
        printf(prompt, login);

    if (result && !FoxAuth_checkPassword(login, getpass(""))) {
        if (!geteuid())
            rootize();
                
        if (result)
            register_self(login, time(NULL) + config.t.seconds + (config.t.minutes * 60) + (config.t.hours * 60 * 60));

        launchWithArgs(argv[1], args);
    } else {
        if (!result) {
            if (!geteuid())
                rootize();
            launchWithArgs(argv[1], args);
        } else {
            printf(wrong);
        }
    }

    return 0;
}