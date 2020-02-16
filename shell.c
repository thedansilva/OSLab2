#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "shell.h"


#define clear() printf("\033[H\033[J")
// #define gotoxy(x, y) printf("\033[%d;%dH", y, x)

int main(int argc, char *argv[], char **envp){
	//clear() already works
	char str[255];
	int pid;
	char command[5];
	char cwd[100];
	char shell[100];
	char args[256][256];
	int argCount = 0;
	char *token;
	while (1) 
	{
	if (getcwd(cwd, sizeof(cwd)) != NULL) 
	{
		strcpy(shell, cwd);
	}
	printf("%s$ ", cwd);
	fgets(str, 255, stdin);
	str[strcspn(str, "\n")] = 0; //remove trailing new line from string before tokenizing
	char orginal[255];
	strcpy(orginal, str);
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
	int pid;
	int forking = 0;
	int batch = 0;
	if(strlen(command)>3){
	char subbuff[4];
	memcpy(subbuff,&command[strlen(command)-3],3);
	subbuff[3]='\0';
	char subbuff2[3];
	memcpy(subbuff2,&command[0],2);
	subbuff2[2]='\0';
		if(strcmp(subbuff, ".sh")==0 && strcmp(subbuff2,"./")==0)
		{
		batch =1;
		}
	}
	if (strcmp(args[argCount - 1], "&") == 0 || strcmp(args[argCount], "&") == 0)
	{
		forking = 1;
	}
	if (strcmp(command, "cd") == 0 || strcmp(command, "cd\n") == 0) 
	{
		if (forking) 
		{
			pid = fork();
			if (pid <= 0) 
			{
				int old_stdout = dup(1);
				freopen("/dev/null", "w", stdout);
				if(strlen(args[0]) <= 0) { //if there's no input past 'cd'
					printcwd;
				} else printf("Directory %s not found\n", args[0]);
				fclose(stdout);
				stdout = fdopen(old_stdout, "w");
				exit(0);
			}
			while ((pid = wait(NULL)) == -1) {
			printf("Process %d done.\n", pid);
			}
		}
		else 
		{	
			if(strlen(args[0]) <= 0) { //if there's no input past 'cd'
				printcwd();
			}
			else
			{
				if (chdir(args[0]) == 0) 
				{
				} else printf("Directory %s not found\n", args[0]);
			}
		}
	}
	else if (strcmp(command, "cls") == 0 || strcmp(command, "cls\n") == 0)
	{
		if (forking)
		{
			pid = fork();
			if (pid <= 0)
			{
				int old_stdout = dup(1);
				freopen("dev/null", "w", stdout);
				clear();
				fclose(stdout);
				stdout = fdopen(old_stdout, "w");
				exit(0);
			}
			while ((pid = wait(NULL)) == -1) {
				printf("Process %d done.\n", pid);
			}
		}
		else
		{
			clear();
		}
	}
	else if (strcmp(command, "dir") == 0 || strcmp(command, "dir\n") == 0)
	{
		if (forking)
		{
			pid = fork();
			if (pid <= 0)
			{
				int old_stdout = dup(1);
				freopen("dev/null", "w", stdout);
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
				fclose(stdout);
				stdout = fdopen(old_stdout, "w");
				exit(0);
			}
			while ((pid = wait(NULL)) == -1) {
				printf("Process %d done.\n", pid);
			}
		}
		else
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
	}
	else if (strcmp(command, "environ") == 0 || strcmp(command, "environ\n") == 0)
	{
		if (forking)
		{
			pid = fork();
			if (pid <= 0)
			{
				int old_stdout = dup(1);
				freopen("dev/null", "w", stdout);
				for (char **env = envp; *env != 0; env++)
				{
					char *thisEnv = *env;
					printf("%s\n", thisEnv);    
				}
				fclose(stdout);
				stdout = fdopen(old_stdout, "w");
				exit(0);
			}
			while ((pid = wait(NULL)) == -1) {
				printf("Process %d done.\n", pid);
			}
		}
		else
		{
			for (char **env = envp; *env != 0; env++)
			{
				char *thisEnv = *env;
				printf("%s\n", thisEnv);    
			}
		}
		}
	else if (strcmp(command, "echo") == 0 || strcmp(command, "echo\n") == 0)
	{
		if (forking)
		{
			pid = fork();
			if (pid <= 0)
			{
				int old_stdout = dup(1);
				freopen("dev/null", "w", stdout);
				for(int i = 0; i < argCount; i++) {
					printf("%s ", args[i]);
				}
				printf("\n");
				fclose(stdout);
				stdout = fdopen(old_stdout, "w");
				exit(0);
			}
			while ((pid = wait(NULL)) == -1) {
				printf("Process %d done.\n", pid);
			}
		}
		else
		{
			for(int i = 0; i < argCount; i++) {
				printf("%s ", args[i]);
			}
			printf("\n");
		}
	}
	else if (strcmp(command, "help") == 0 || strcmp(command, "pause\n") == 0)
	{
		if (forking)
		{
		pid = fork();
		if (pid <= 0)
		{
			int old_stdout = dup(1);
			freopen("dev/null", "w", stdout);
			help();
			fclose(stdout);
			stdout = fdopen(old_stdout, "w");
			exit(0);
		}
		while ((pid = wait(NULL)) == -1) {
			printf("Process %d done.\n", pid);
		}
		}
		else
		{
			help();
		}
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
	else if(batch==1){
		system(orginal);
	}
	else
	{
		int status;
		printf("Unknown command. Invoking %s on native bash.\n", command);
		pid = fork();
		if (pid > 0)
		{
			waitpid(pid, &status, 0);
		}
		else
		{
		execl(shell, command, NULL);
		}
	}
	memset(args, 0, sizeof(args));
	memset(str, 0, 255);
	}
}
