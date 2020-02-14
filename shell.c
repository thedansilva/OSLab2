#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

#define clear() printf("\033[H\033[J")
// #define gotoxy(x, y) printf("\033[%d;%dH", y, x)

int main(int argc, char *argv[]){
	//clear() already works
	char str[255];
	char command[5];
	char cwd[100];
	char args[256][256];
	int argCount = 0;
	char *token;
	while (1) 
	{
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
	}
	printf("%s$ ", cwd);
	fgets(str, 255, stdin);
	str[strcspn(str, "\n")] = 0; //remove trailing new line from string before tokenizing
	token = strtok(str, " ");
	argCount = 0;
	strcpy(command, token);
	while(token != NULL) {
		token = strtok(NULL, " ");
		if (token != NULL) {
			//printf("Current token is %s\n", token);
			strcpy(args[argCount], token);
			argCount++;
		}

	}
	if (strcmp(command, "cd") == 0 || strcmp(command, "cd\n") == 0) {
		if(strlen(args[0]) <= 0) { //if there's no input past 'cd'
			printcwd();
		}
		else {
			if (chdir(args[0]) == 0) 
			{
			} else printf("Directory %s not found\n", args[0]);
		}
	}
	memset(args, 0, sizeof(args));
	memset(str, 0, 255);
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
