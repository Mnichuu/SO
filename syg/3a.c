#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

int main(int argc, char *argv[]) 
{
    int status;
    pid_t wpid;

    if(argc!=3)
    {
        fprintf(stderr, "Nieprawidlowa liczba arg\n");
        exit(EXIT_FAILURE);
    }
    int sign=atoi(argv[2]);
    setpgid(0, 0); // 0,0 zeby stawal sie liderem swojej grupy procesow
    for(int i=0; i<3; ++i)
    { 
        switch (fork()) 
        {
            case 0:
                execlp("./1", "1", argv[1], argv[2], NULL);
                perror("execl error");
                exit(EXIT_FAILURE);
                break;

            case -1:
                perror("fork error");
                exit(EXIT_FAILURE);
                break;
                
            default: 
                if(signal(sign,SIG_IGN)==SIG_ERR)
                {
                    perror("Funkcja signal ma problem z SIGTERM");
                    exit(EXIT_FAILURE);
                }
                break;
        }
    }
    /*while( j > 0 )
    {
        if ( wait(NULL) == 0 )
        {
            perror("wait error\n");
            exit(EXIT_FAILURE);
        }
        else
        j--;
    }*/
    while((wpid = wait(&status) )>0); // czeka az wszystkie procesy potomne sie zakoncza
}
