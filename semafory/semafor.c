#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>




sem_t *stworz_semafor(const char *name)
{
	sem_t *ip_semafora;
	if ((ip_semafora=sem_open(name, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
	{
		perror("blad stworzenia semafora");
		exit(EXIT_FAILURE);
	}
	else
	{
		return ip_semafora;
	}
}

sem_t *otworz_semafor(const char *name)
{
	sem_t *ip_semafora;
	if ((ip_semafora=sem_open(name, 0)) == SEM_FAILED)
	{
		perror("blad otworzenia semafora");
		exit(EXIT_FAILURE);
	}
	else
	{
		return ip_semafora;
	}
}

void otrzymaj_wartosc_semafora(sem_t *sem, int *sval)
{
	if (sem_getvalue(sem, sval) == -1)
	{
		perror("blad otrzymania wartosci semafora");
		exit(EXIT_FAILURE);
	}
}

void podnies_semafor(sem_t *sem)
{
	if(sem_post(sem) == -1)
	{
		perror("blad podniesienia semafora");
		exit(EXIT_FAILURE);
	}
}

void opusc_semafor(sem_t *sem)
{
	if(sem_wait(sem) == -1)
	{
		perror("blad opuszczenia semafora");
		exit(EXIT_FAILURE);
	}
}

void zamknij_semafor(sem_t *sem)
{
	if(sem_close(sem) == -1)
	{
		perror("blad zamkniecia semafora");
		exit(EXIT_FAILURE);
	}
}

void usun_semafor(const char *name, int oflag)
{
	if(sem_unlink(name) == -1)
	{
		perror("blad usuniecia semafora");
		exit(EXIT_FAILURE);
	}
}