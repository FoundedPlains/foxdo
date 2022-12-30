#include "config_parser.h"
#include "../foxstd.h"

Config parseConfig() {
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

    freeDict(&dict);

    return config;
}