#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "shell.h"

#define clear() printf("\033[H\033[J")
// #define gotoxy(x, y) printf("\033[%d;%dH", y, x)

int main(int argc, char *argv[], char **envp){
	//clear() already works
	char str[255];
	char command[5];
	char cwd[100];
	char args[256][256];
	int argCount = 0;
	char *token;
	while (1) 
	{
	if (getcwd(cwd, sizeof(cwd)) != NULL) 
	{
	}
	printf("%s$ ", cwd);
	fgets(str, 255, stdin);
	str[strcspn(str, "\n")] = 0; //remove trailing new line from string before tokenizing
	token = strtok(str, " ");
	argCount = 0;
	strcpy(command, token);
	while(token != NULL) 
	{
		token = strtok(NULL, " ");
		if (token != NULL) 
		{
			//printf("Current token is %s\n", token);
			strcpy(args[argCount], token);
			argCount++;
		}

	}
	if (strcmp(command, "cd") == 0 || strcmp(command, "cd\n") == 0) 
	{
		if(strlen(args[0]) <= 0) { //if there's no input past 'cd'
			printcwd();
		}
		else {
			if (chdir(args[0]) == 0) 
			{
			} else printf("Directory %s not found\n", args[0]);
		}
	}
	else if (strcmp(command, "cls") == 0 || strcmp(command, "cls\n") == 0)
	{
		clear();
	}
	else if (strcmp(command, "dir") == 0 || strcmp(command, "dir\n") == 0)
	{
		DIR *dir;
		struct dirent *dirent;
		if (strlen(args[0]) <= 0) 
		{
		dir = opendir(".");
		}
		else
		{
		dir = opendir(args[0]);
		}
		if (dir) 
		{
			while ((dirent = readdir(dir)) != NULL)
				{
				printf("%s\n", dirent->d_name);
				}
			closedir(dir);
		}	
	}
	else if (strcmp(command, "environ") == 0 || strcmp(command, "environ\n") == 0)
	{
		for (char **env = envp; *env != 0; env++)
		{
			char *thisEnv = *env;
			printf("%s\n", thisEnv);    
		}
	}
	else if (strcmp(command, "echo") == 0 || strcmp(command, "echo\n") == 0)
	{
		for(int i = 0; i < argCount; i++) {
			printf("%s ", args[i]);
		}
		printf("\n");
	}
	else if (strcmp(command, "help") == 0 || strcmp(command, "pause\n") == 0)
	{
		help();
	}
	else if (strcmp(command, "pause") == 0 || strcmp(command, "pause\n") == 0)
	{
		char resumer[256];
		printf("Pausing shell until Enter is pressed.\n");
		fgets(resumer, sizeof(resumer), stdin);
		do 
		{
			fgets(resumer, sizeof(resumer), stdin);
		} while (strcmp(resumer, "\n") != 0); 
		printf("Resuming.\n");
		
	}
	else if (strcmp(command, "quit") == 0 || strcmp(command, "quit\n") == 0)
	{
		return 0;
	}
	else
	{
		printf("***\nUnknown command. Invoking %s on native bash.\n", command);
		system(command);
		printf("***\n");
	}
	memset(args, 0, sizeof(args));
	memset(str, 0, 255);
	}
}
