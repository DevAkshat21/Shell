#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#define PATH_DELIMITER ";"
#define DIR_SEPARATOR "\\"
#define ACCESS _access
#define ACCESS_MODE 0
#else
#include <unistd.h>
#define PATH_DELIMITER ":"
#define DIR_SEPARATOR "/"
#define ACCESS access
#define ACCESS_MODE X_OK
#endif

char *find_path(char *arg) {
    static char full_path[1024];

    char path_copy[4096];
    strcpy(path_copy, getenv("PATH"));

    char *dir = strtok(path_copy, PATH_DELIMITER);

    while (dir != NULL) {

        strcpy(full_path, dir);
        strcat(full_path, DIR_SEPARATOR);
        strcat(full_path, arg);

        if (ACCESS(full_path, ACCESS_MODE) == 0) {
            return full_path;
        }

        dir = strtok(NULL, PATH_DELIMITER);
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    setbuf(stdout, NULL);

    while (1) {

        printf("$ ");

        char command[1024];

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        command[strcspn(command, "\r\n")] = '\0';

        char *builtin = strtok(command, " ");
        char *arg = strtok(NULL, "");

        if (builtin == NULL)
            continue;

        // Exit
        if (strcmp(builtin, "exit") == 0) {
            break;
        }

        // Echo
        else if (strcmp(builtin, "echo") == 0) {
            printf("%s\n", arg ? arg : "");
        }

        // Type
        else if (strcmp(builtin, "type") == 0) {

            if (arg == NULL) {
                printf("type: missing argument\n");
            }

            else if (!strcmp(arg, "exit") ||
                     !strcmp(arg, "echo") ||
                     !strcmp(arg, "type")) {

                printf("%s is a shell builtin\n", arg);
            }

            else {

                char *path = find_path(arg);

                if (path != NULL)
                    printf("%s is %s\n", arg, path);
                else
                    printf("%s: not found\n", arg);
            }
        }

        // Unknown command
        else {
            printf("%s: command not found\n", builtin);
        }
    }

    return 0;
}