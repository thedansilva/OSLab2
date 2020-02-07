#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

#define clear() printf("\033[H\033[J")
// #define gotoxy(x, y) printf("\033[%d;%dH", y, x)

int main(){
	//clear() already works
	
	char str[255];
	char command[5];
	char *token;
	printf("Type some stuff: ");
	fgets(str, 255, stdin);
	token = strtok(str, " ");
	strcpy(command, token);
	printf("Command is %s\n", command);
	token = strtok(NULL, " ");
	while(token != NULL) {
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}
        if (strcmp(command, "cd") == 0 || strcmp(command, "cd\n") == 0){
		printcwd();
	}
    	//showsomething();
}

void print_env_vars() {
    // const char* s = getenv("USER");
    const char* s = getenv("PATH");
    printf("%s\n", (s != NULL) ? s : "");
}

void printcwd() {
	char cwd[100];
	if(getcwd(cwd, sizeof(cwd)) != NULL){
		printf("%s\n", cwd);
	}
}
