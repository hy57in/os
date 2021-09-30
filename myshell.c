#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define MAXa 1024
#define MAXb 100

void type_propmt() {
    printf("KimHyoJin$");
}

void read_command(char cmd[], char *par[]) {
    char line[MAXa];
    int count = 0, i = 0, j = 0;
    char *arr[MAXb], *piece;

    while(TRUE) {
        int c = fgetc(stdin);
        line[count++] = (char)c;
        if(c == "\n") break;

    }
    if(count == 1) return;
    piece = strtok(line, "\n\t");
    while(piece != NULL) {
        arr[i++] = strdup(piece);
        piece = strtok(NULL, "\n\t");
    }
    strcpy(cmd, arr[0]);
    for(j = 0; j < i; j++) {
        par[j] = arr[j];
    }
    par[i] = NULL;

}

int main() {
    char temp[MAXb], command[MAXb], *parameters[MAXb];
    char *envp[] = {(char *) "PATH = /bin", 0};

    while(TRUE) {
        type_propmt();
        read_command(command, parameters);

        if(strcmp(command, "exit") == 0) {
            exit(TRUE);
        } else {
            if(fork() != 0) {
                printf("Parents retrn\n");
                wait(NULL);
                printf("Parents return\n");
            } else {
                strcpy(temp, "/bin/");
                strcat(temp, command);
                execve(temp, parameters, envp);
            } 
        }
        
    }

    return 0;
}