#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h> 

int main(int argc, char *argv[])
{
	if (argc != 3) // 3 bo 1-nazwa programu, 2-d,i lub p, 3-nr sygnalu
	{
		perror ("Nieprawidlowa liczba arg");
		exit (EXIT_FAILURE);
	}
	
	int sygnal = atoi (argv[2]); // zamiana numeru sygnalu z char na int + przechowanie
	printf ("Uruchamiam program 1.c z parametrem \"%s\" \n", argv[1]);
	int pid=fork();
	switch (pid)
	{
		case -1:
			perror ("Nie udalo sie utworzyc procesu potomnego");
			exit (EXIT_FAILURE);
			break;

		case 0:
			execlp("./1", "1", argv[1], argv[2], NULL); // uruchamianie 1.c przy pomocy execlp
			break;
		
		default:
			sleep(1);
			if(kill(pid,0) == -1)
			{
				perror("Proces nie istnieje!");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf ("Sygnal %d został wyslany do procesu o id: %d\n", sygnal, pid);
				kill(pid, sygnal);
			}
			break;
	}
	printf ("Koniec\n");
	return 0;
}