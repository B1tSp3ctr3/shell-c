#include <stdio.h>
#include <string.h>
int main() {
  // Flush after every printf
  setbuf(stdout, NULL);

  char input[100];
  while(1){
	  fgets(input, 100, stdin);
	  if(strcmp(input,"exit 0")==0) return 0;
	  printf("$ ");
    	  input[strlen(input)-1]='\0';
	  printf("%s: command not found\n",input);
  }
  return 0;
}
	
