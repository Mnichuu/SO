#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
 

int main(int argc, char const *argv[])
{
	printf("==PROCES MACIERZYSTY==\n"); 
	printf("PID: %d\n", getpid()); // zwraca id procesu
	printf("PPID: %d\n", getppid()); //zwraca id procesu rodzica
	printf("PGID: %d\n", getpgid(getpid())); //zwraca id grupy procesów
	printf("UID: %d\n", getuid()); 
	printf("GID: %d\n", getgid()); 
	printf("==PROCESY POTOMNE==\n");

for(int i=0; i<3; i++)
{
	switch (fork()) // zwraca wartosc 0 kiedy proces jest procesem potomnym, -1 dla bledu, default czeka az pierwszy proces potomny sie zakonczy
	{
		case -1:
		perror("fork error");
		exit(1);
		case 0:
		{
			printf("PID: %d\n", getpid()); 
			printf("PPID: %d\n", getppid());
			printf("PGID: %d\n", getpgid(getpid())); 
			printf("UID: %d\n", getuid());
			printf("GID: %d\n", getgid());
			printf("\n");
		}
		default:
		{
				wait(NULL); 
		}
	}
};
	return 0;
}
