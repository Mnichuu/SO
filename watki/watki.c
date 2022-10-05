#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

pthread_t utworz_watek (void *funkcja(void *), void *argument) 
{
	pthread_t adres_watku;
	int status = pthread_create (&adres_watku, NULL, funkcja, argument);
	// kody bledu dla niezerowej wartosci pthread_creat
	if (status == EAGAIN) 
	{
		printf ("Błąd przy tworzeniu wątku!\n");
		printf ("Przekroczony został limit systemowy liczby wątków lub procesów LWP\n");
		exit (EXIT_FAILURE);
	} else if (status == ENOMEM) 
	{
		printf ("Błąd przy tworzeniu wątku!\n");
		printf ("Brak pamięci do utworzenia nowego wątku\n");
		exit (EXIT_FAILURE);
	} else if (status == EINVAL) 
	{
		printf ("Błąd przy tworzeniu wątku!\n");
		printf ("Nieprawidłowa wartość argumentu attr");
		exit (EXIT_FAILURE);
	}
	return adres_watku;
}

void polacz_watek (pthread_t watek) 
{
	if (pthread_join (watek, NULL) != 0) // dołączanie wątku plus czekanie az watek sie skonczy przez NULL
	{
		printf("Błąd łączenia wątku!\n");
		exit(EXIT_FAILURE);	
	}
}

void inicjalizuj_mutex (pthread_mutex_t *mutex) 
{
	if (pthread_mutex_init(mutex, NULL) != 0) // inicjalizowanie mutexu jako otwartego przez NULL 
	{
		printf("Błąd przy inicjalizacji mutexu!\n");
		exit(EXIT_FAILURE);
	}
}

void zamknij_mutex (pthread_mutex_t *mutex) 
{
	if (pthread_mutex_lock(mutex) != 0) 
	{
		printf("Błąd zamykania mutexu!\n");
		exit(EXIT_FAILURE);	
	}
}

void otworz_mutex (pthread_mutex_t *mutex) 
{
	if (pthread_mutex_unlock(mutex) != 0) 
	{
		printf("Błąd otwierania mutexu!\n");
		exit(EXIT_FAILURE);
	}
}

void usun_mutex (pthread_mutex_t *mutex) 
{
	if (pthread_mutex_destroy (mutex) != 0) 
	{
		printf ("Błąd usuwania mutexu!\n");
		exit (EXIT_FAILURE);
	}
}