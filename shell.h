#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void showsomething(){
    printf("Hmm it showed something\n");
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

void help() {
	printf("*****\ncd <directory>: change directory (or leave blank to see cwd)\nclr: clear screen\ndir <directory>: list contents of directory\nenviron: list environment strings\necho <comment>: display a comment\nhelp: display this help\npause: pause the shell until enter is pressed\nquit: quit the shell\nAdditionally, you may execute any native bash shell function outside\nof these, but they are not from this shell itself.\n*****\n");
}
