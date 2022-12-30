#include "check.h"

#include <string.h>
#include <stdlib.h>
#include <grp.h>
#include <unistd.h>
#include <termios.h>
#include <linux/limits.h>

short check_groups(Config conf) {
    __gid_t user_groups[NGROUPS_MAX];

    int size = getgroups(NGROUPS_MAX, user_groups);
    for (int i = 0; i < size; i++) {
        struct group *grp = getgrgid(user_groups[i]);
        size_t len = strlen(grp->gr_name);
        for (int j = 0; j < conf.a.groups.length; j++) {
            if (!strncmp(grp->gr_name, conf.a.groups.data[j], len))
                return 1;
        }
    }

    return 0;
}

short check_user(Config conf) {
    const char *login = getenv("USER");

    unsigned long name_len = strlen(login);
    for (int i = 0; i < conf.a.users.length; i++) {
        if (!strncmp(login, conf.a.users.data[i], name_len))
            return 1;
    }

    return 0;
}