#include "foxstd.h"
#include "src/rootize.h"
#include "src/launch.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <bits/local_lim.h>

char *get_login() {
    char *login = getenv("USER");
    return login;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("foxdo [PROG] [ARGS]\n");
        return 0;
    }

    if (argc == 2) {
        char *login = get_login();
        printf(prompt, login);

        if (!FoxAuth_checkPassword(login, getpass(""))) {
            if (!geteuid())
                rootize();
            launchWithoutArgs(argv[1]);
        } else {
            printf(wrong);
        }

    } else {
        char *args[argc - 1];

        for (int i = 1; i < argc; i++) {
            args[i - 1] = argv[i];
        }

        args[argc - 1] = NULL;

        char *login = get_login();

        printf(prompt, login);
        if (!FoxAuth_checkPassword(login, getpass(""))) {
            if (!geteuid())
                rootize();
            launchWithArgs(argv[1], args);
        } else {
            printf(wrong);
        }
    }
}