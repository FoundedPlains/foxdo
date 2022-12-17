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