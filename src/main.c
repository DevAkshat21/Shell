#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
char *find_path(char *arg) {
    static char full_path[1024];

    char path_copy[4096];
    strcpy(path_copy, getenv("PATH"));

    // Windows PATH is separated by ';'
    char *dir = strtok(path_copy, ";");

    while (dir != NULL) {

        strcpy(full_path, dir);
        strcat(full_path, "\\");
        strcat(full_path, arg);

        // Does this file exist?
        if (_access(full_path, 0) == 0) {
            return full_path;
        }

        dir = strtok(NULL, ";");
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    setbuf(stdout, NULL);

    int i = 1;

    while (i == 1) {

        printf("$ ");

        char command[1024];
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\r\n")] = '\0';

        char *builtin = strtok(command, " ");
        char *arg = strtok(NULL, "");

        if (builtin == NULL)
            continue;

        // Exit
        if (strcmp(builtin, "exit") == 0) {
            i = 0;
        }

        // Echo
        else if (strcmp(builtin, "echo") == 0) {
            printf("%s\n", arg ? arg : "");
        }

        // Type
        else if (strcmp(builtin, "type") == 0) {

            if (!strcmp(arg, "type") ||
                !strcmp(arg, "echo") ||
                !strcmp(arg, "exit")) {

                printf("%s is a shell builtin\n", arg);
            }
            else {
            char *path = find_path(arg);

            if (path != NULL) {
                printf("%s is %s\n", arg, path);
            } else {
                printf("%s: not found\n", arg);
                }
            }
        }

        // Unknown command
        else {
            printf("%s: command not found\n", builtin);
        }
    }

    return 0;
}