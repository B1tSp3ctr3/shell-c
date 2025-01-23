#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
  // Flush after every printf
  setbuf(stdout, NULL);

  char input[100];
  while (1)
  {
    printf("$ ");
    fgets(input, 100, stdin);
    char builtins[][20] = {
        "echo",
        "type",
        "exit"};
    char *path = getenv("PATH");
    input[strlen(input) - 1] = '\0';
    // exit command
    if (strcmp(input, "exit 0") == 0)
      exit(0);
    // type command
    if (strncmp(input, "type ", strlen("type ")) == 0)
    {
      char *arguments = input + 5;
      int found = 0;
      for (int i = 0; i < sizeof(builtins) / 20; i++)
      {
        if (strcmp(builtins[i], arguments) == 0)
        {
          printf("%s is a shell builtin\n", arguments);
          found = 1;
          break;
        }
      }
      if (found == 0)
      {
        char *directory = strktok(path, ":");
        while (directory != NULL)
        {
          char *command = malloc(strlen(directory) + strlen(arguments) + 2);
          strcpy(command, directory);
          strcat(command, "/");
          strcat(command, arguments);
          if (access(arguments, F_OK) == 0)
          {
            printf("%s is %s\n", arguments, command);
            found = 1;
            break;
          }
          directory = strtok(NULL, ":");
        }
        printf("%s: not found\n", input + 5);
      }
    }
    // echo command
    else if (strncmp(input, "echo ", strlen("echo ")) == 0)
    {
      printf("%s\n", input + strlen("echo "));
    }
    else if (strcmp(input, "echo") == 0)
    {
      printf("\n");
    }

    else
      printf("%s: command not found\n", input);
  }
  return 0;
}
