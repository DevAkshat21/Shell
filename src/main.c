#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  
  // Flush after every printf
  setbuf(stdout, NULL);
  // Captures the user's command in the "command" variable
  char command[1024];
  fgets(command, sizeof(command), stdin);
  // Remove the trailing newline
  command[strcspn(command, "\n")] = '\0';

  // Prints the "<command>: command not found" message
  printf("%s: command not found\n", command);


  printf("$ ");

  return 0;
}
