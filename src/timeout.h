#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <stdint.h>

void register_self(char *username, int64_t timeout);
short check_self(char *username, int64_t currentTime);

#endif