#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

int main() {
    char linha[MAX_LINE];
    char *args[MAX_ARGS];

    while (1){
        printf("meu_shell> ");
        fflush(stdout);

        if(fgets(linha, sizeof(linha), stdin)==NULL){
            break;
        }

        linha[strcspn(linha, "\n")] = '\0';

        int i = 0;
        args[i] = strtok(linha, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if(args[0]==NULL){
            continue;
        }

        if(strcmp(args[0], "exit")==0){
            printf("Saindo do shell.\n");
            break;
        }

        pid_t pid = fork();

        if(pid<0){
  
            perror("Erro ao executar fork");
            exit(1);
        } 
        else if(pid==0){
            if(execvp(args[0], args)<0){
                printf("Comando nao encontrado: %s\n", args[0]);
                exit(1);
            }
        } 
        else{
            int status;
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}
