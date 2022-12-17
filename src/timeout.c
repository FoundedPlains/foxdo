#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include <sys/stat.h>

#include "timeout.h"

#define itoa(x) #x

void register_self(char *username, int64_t timeout) {
    DIR *foxdo = opendir("/tmp/foxdo/");

    if (foxdo) {
        char path[strlen("/tmp/foxdo/") + strlen(username) + 1];
        char *ptr = path;
        *ptr = '\0';
        strcat(ptr, "/tmp/foxdo/");
        strcat(ptr, username);

        DIR *user = opendir(ptr);
        if (user) {
            char ppid_str[strlen(itoa(PID_MAX_LIMIT)) + 2];
            sprintf(ppid_str, "%d", getppid());

            char finalPath[strlen(ptr) + strlen(ppid_str)];
            char *finalPtr = finalPath;
            *finalPtr = '\0';
            strcat(finalPtr, ptr);
            strcat(finalPtr, "/");
            strcat(finalPtr, ppid_str);

            FILE *fw = fopen(finalPath, "w");
            fwrite(&timeout, sizeof(int64_t), 1, fw);
            fclose(fw);
            closedir(user);
        } else {
            mkdir(ptr, 0755);
            register_self(username, timeout);
        }
        closedir(foxdo);
    } else {
        mkdir("/tmp/foxdo/", 0755);
        register_self(username, timeout);
    }
}

short check_self(char *username, int64_t currentTime) {
    DIR *foxdo = opendir("/tmp/foxdo/");

    if (foxdo) {
        char path[strlen("/tmp/foxdo/") + strlen(username) + 1];
        char *ptr = path;
        *ptr = '\0';
        strcat(ptr, "/tmp/foxdo/");
        strcat(ptr, username);

        DIR *user = opendir(ptr);
        if (user) {
            char ppid_str[strlen(itoa(PID_MAX_LIMIT)) + 2];
            sprintf(ppid_str, "%d", getppid());

            char finalPath[strlen(ptr) + strlen(ppid_str)];
            char *finalPtr = finalPath;
            *finalPtr = '\0';
            strcat(finalPtr, ptr);
            strcat(finalPtr, "/");
            strcat(finalPtr, ppid_str);

            FILE *fr = fopen(finalPath, "r");
            if (!fr)
                return 1;
            int64_t saved;
            fread(&saved, sizeof(int64_t), 1, fr);
            fclose(fr);

            closedir(user);
            return currentTime > saved;
        } else {
            return 1;
        }
        closedir(foxdo);
    } else {
        return 1;
    }
}