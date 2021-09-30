#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1

void type_propmt() {
    printf("KimHyoJin$");
}

void read_command(char commands[], char *parameters[]) {
    char line[1024], *input[100], *args;
    int cnt = 0, k = 0;

    while(TRUE) {
        int arg = fgetc(stdin);

        line[cnt++] = (char)arg;
        if(arg == '\n') break;
    }

    if(cnt == 1) return;

    args = strtok(line, "\n\t");

    while(args != NULL) {
        input[k++] = strdup(args);
        args = strtok(NULL, "\n\t");
    }

    strcpy(commands, input[0]);

    for(int i = 0; i < k; i++) {
        parameters[i] = input[i];
    }

    parameters[k] = NULL;
}

int main() {
    char temp[100], command[100], *parameters[100];
    char *envp[] = {(char *) "PATH=/bin", 0};
    pid_t pid;
    pid = fork();

    while(TRUE) {
        type_propmt();
        read_command(command, parameters);

        if(strcmp(command, "exit") == 0) { //exit
            exit(TRUE);
        }
        if(pid < 0) {
            fprintf(stderr, "fork failed\n");
        } else if(pid == 0) {
            strcpy(temp, "/bin/");
            strcat(temp, command);
            execve(temp, parameters, envp);
            //execlp("/bin/ls", "ls", NULL);
        } else {
            printf("parent return\n");
            wait(NULL);
            printf("child complete\n");
        }
    }

    return 0;
}