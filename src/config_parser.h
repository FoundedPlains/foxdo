#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "../foxstd.h"

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

Config parseConfig();

#endif