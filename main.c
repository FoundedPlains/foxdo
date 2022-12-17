#include "foxstd.h"
#include "src/rootize.h"
#include "src/launch.h"
#include "src/timeout.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <linux/limits.h>
#include <grp.h>
#include <unistd.h>
#include <termios.h>

typedef struct {
    StringArray users;
    StringArray groups;
} Allow;

typedef struct {
    Number seconds;
    Number minutes;
    Number hours;
} Timeout;

typedef struct {
    Allow a;
    Timeout t;
} Config;

char *get_login()
{
    char *login = getenv("USER");
    return login;
}

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

    Dict dict = newDict();

    Config config;

    config.t.hours = 0;
    config.t.minutes = 0;
    config.t.seconds = 0;

    assingDict(&dict, "allow.users", StringArray_type, &config.a.users);
    assingDict(&dict, "allow.groups", StringArray_type, &config.a.groups);
    assingDict(&dict, "timeout.seconds", Number_type, &config.t.seconds);
    assingDict(&dict, "timeout.minutes", Number_type, &config.t.minutes);
    assingDict(&dict, "timeout.hours", Number_type, &config.t.hours);

    parse("/etc/foxdo.foxconfig", &dict);

    short has_group = 0;
    short has_user = 0;

    __gid_t user_groups[NGROUPS_MAX];

    int size = getgroups(NGROUPS_MAX, user_groups);
    for (int i = 0; i < size; i++) {
        struct group *grp = getgrgid(user_groups[i]);
        size_t len = strlen(grp->gr_name);
        for (int j = 0; j < config.a.groups.length; j++) {
            if (!strncmp(grp->gr_name, config.a.groups.data[j], len))
                has_group = 1;
        }
    }

    char *login = get_login();

    int name_len = strlen(login);
    for (int i = 0; i < config.a.users.length; i++) {
        if (!strncmp(login, config.a.users.data[i], name_len))
            has_user = 1;
    }

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