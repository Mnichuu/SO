#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h> 

void sighandler (int s)
{
	printf ("Posiadany sygnal: %d\n", s);
}

int main (int argc, char *argv[])
{
	
	if (argc != 3) // 3 bo 1-nazwa programu, 2-d,i lub p, 3-nr sygnalu
	{
		fprintf (stderr, "Nieprawidlowa liczba arg\n");
		exit (EXIT_FAILURE);
	}
	
	int sig = atoi(argv[2]); // zamiana numeru sygnalu z char na int + przechowanie
	printf("%c\n", argv[1][0]);

	if ( strcmp (argv[1], "d") == 0 ) // wykonanie operacji domyslnej dla sygnalu
	{
		if ( signal (sig, SIG_DFL) == SIG_ERR )
		{
			perror ("Wystapil problem z SIG_DFL");
			exit (EXIT_FAILURE);
		}
	}
	
	else
	
	if ( strcmp (argv[1], "i") == 0 ) // ignorowanie sygnalu
	{
		if ( signal (sig, SIG_IGN) == SIG_ERR )
		{
			perror ("Wystapil problem z SIG_IGN");
			exit (EXIT_FAILURE);
		}
	}
	
	else
	
		if ( strcmp (argv[1], "p") == 0 ) //przechwycenie i wlasna obsluga sygnalu
	{
		if ( signal (sig, sighandler) == SIG_ERR )
		{
			perror ("Wystapil problem z sighandler");
			exit (EXIT_FAILURE);
		}
	}
	
	else
	
	{
		perror ("Wprowadzono zly pierwszy argument");
		exit (EXIT_FAILURE);
	}

	pause ();
	
	printf ("Koniec\n");
	return 0;
}
