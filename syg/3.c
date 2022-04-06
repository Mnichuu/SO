#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

int main(int argc, char *argv[]) 
{
    int pid;// przechowuje id procesu 
    int sig=atoi(argv[2]);

    switch (pid = fork()) 
    {
        case 0: //potomny
            if (execlp("./3a", "3a", argv[1], argv[2], NULL) == -1) 
            {
                perror("execl error");
                exit(EXIT_FAILURE);
            }
            break;

        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
            break;

        default: // macierzysty 
        {
            sleep(1); // tworzy podgrupy w tym czasie
            if(kill(-pid, 0) == -1) 
            {
                if(errno == -1)
                {
                    perror("proces nie istnieje");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                kill(-pid,sig);// kill do wszystkich procesów podgrupy
            }

            if (wait(NULL) == -1) 
            {
                perror("wait error");
                exit(EXIT_FAILURE);
            }
            break;
        }
    }
    return 0;
}
