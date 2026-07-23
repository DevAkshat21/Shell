#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


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

// Find the full path of a command in the PATH environment variable

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




//main function 

int main(int argc, char *argv[]) {

    setbuf(stdout, NULL);

    while (1) {

        printf("$ ");

        char command[1024];

    

        if (fgets(command, sizeof(command), stdin) == NULL)
        break;

        command[strcspn(command, "\r\n")] = '\0';

            char *argv[100];
            int argc = 0;

            char *token = strtok(command, " ");

            while (token != NULL) {
                argv[argc] = token;
                argc++;

                token = strtok(NULL, " ");
            }
            argv[argc] = NULL;
            char *builtin = argv[0];

            if (builtin == NULL) {
                continue;
}

        // Exit

        if (strcmp(builtin, "exit") == 0) {
            break;
        }

        // Echo

        else if (strcmp(builtin, "echo") == 0) {
            int i = 1;
            while (argv[i] != NULL){
                if (i>1){
                     printf(" %s",argv[i]);
                }
                else{
                    printf("%s",argv[i]);
                }
                i++;
            }
            printf("\n");
            continue;
        }

        // Type

        else if (strcmp(builtin, "type") == 0) {

            int i = 1 ;
            if (argv[i] == NULL) {
                printf("type: missing argument\n");
            }

            else if (!strcmp(argv[i], "exit") ||
                     !strcmp(argv[i], "echo") ||
                     !strcmp(argv[i], "type") ||
                     !strcmp(argv[i], "cd") ||
                     !strcmp(argv[i],"pwd")) {

                printf("%s is a shell builtin\n", argv[i]);
            }

            else {

                char *path = find_path(argv[i]);

                if (path != NULL)
                    printf("%s is %s\n", argv[i], path);
                else
                    printf("%s: not found\n", argv[i]);
            }
            continue;


        }

        if (builtin == NULL){
            continue;
        }

        // Pwd 

        else if(strcmp(builtin,"pwd")==0){
            char cwd[1024];
            if (getcwd(cwd,sizeof(cwd))!= NULL){
                printf("%s\n",cwd);
            }
            else{
                perror("pwd");
            }
            continue;
        }


        // Execute external command

        char *path = find_path(builtin);

        if (path != NULL) {
            pid_t pid = fork();

            if (pid == 0) {
                execv(path, argv);
                perror("execv");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                wait(NULL);
            } else {
                perror("fork");
                exit(EXIT_FAILURE);
            }
        }

        //cd 

        else if (strcmp(builtin,"cd")==0){

            if(strcmp(argv[1],"~")==0){
                chdir((getenv("HOME")));
            }            
            
            else if(chdir(argv[1])!=0){
                printf("cd: %s: %s\n",argv[1],strerror(errno));
            }

            else{
                continue;
            }
        }



        // Unknown command
        else {
            printf("%s: command not found\n", builtin);
        }
    }

    return 0;
}