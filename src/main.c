#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  // Flush after every printf
  setbuf(stdout, NULL);
  int i;
  i = 1;
  while (i == 1)
  {
  printf("$ ");

  // Captures the user's command in the "command" variable
  char command[1024];
  fgets(command, sizeof(command), stdin);

  // Remove the trailing newline
  command[strcspn(command, "\r\n")] = '\0';
  if (strcmp(command,"exit") == 0){
    i = 0;
  }

  else if (strncmp(command, "echo ", 5) == 0) {
    printf("%s\n", command+5);
  }

  else if(strncmp(command, "type ",5)==0){
    if(strncmp(command+5, "echo" ,4)==0){
      printf("%s is a shell builtin \n" ,command+5);
    }
    else if(strncmp(command+5, "type " ,4)==0){
      printf("%s is a shell builtin \n" ,command+5);
    }
    else if(strncmp(command+5, "exit " ,4)==0){
      printf("%s is a shell builtin \n" ,command+5);
    }
    else{
      printf("%s: not found\n",command+5);
    }
  }

  // Prints the "<command>: command not found" message
  else{
  printf("%s: command not found\r\n", command);
  }
  }
  



  return 0;
}
