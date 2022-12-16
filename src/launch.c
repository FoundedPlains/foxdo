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