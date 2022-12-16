#include <unistd.h>

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
    return 0;
}