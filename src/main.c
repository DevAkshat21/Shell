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
  // Prints the "<command>: command not found" message
  else{
  printf("%s: command not found\r\n", command);
  }
  }
  



  return 0;
}
