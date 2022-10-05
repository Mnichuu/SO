#define _REENTRANT // aby móc korzystać z biblioteki fukcji wątkowych standardu POSIX używam dyrektyw, kod wielokrotnego użytku
#include <pthread.h> //

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "watki.h"

#define max_liczba_watkow 10 //ustawianie maksymalnej liczby watkow

int liczba;
int *ppamiec;
unsigned int liczba_watkow;
unsigned int liczba_sekcji;
pthread_t watki[max_liczba_watkow];
pthread_mutex_t mutex; //tworzenie mutexu
const double min_dlugosc_czekania = 1.0;
const double max_dlugosc_czekania = 4.0 - min_dlugosc_czekania;

void random_wait(const double max_dlugosc_czekania, const double min_dlugosc_czekania) // czekanie losowej ilosci czasu
{
	sleep ((double)(rand() % (int)(max_dlugosc_czekania * 100)) / 100 + min_dlugosc_czekania);
}

void ustaw_kursor (unsigned x, unsigned y) // funkcja z hello.c
{
	printf ("\033[%d;%dH\033[2K", y, x);
}

void *watek_start (void *argument) 
{
	
	int counter = 0;
	int nr_watku = *(int *)argument; // rzutowanie argumentu z void na int
	srand (time (NULL));
	
	printf ("Wątek nr: %d, ID: %ld \n", nr_watku + 1, watki[nr_watku]);
	
	sleep (1);
	
	for (int i = 0; i < liczba_sekcji; i++) // petla ktora wykonuje sie tyle razy co ilosc sekcji krytycznych 
	{
		
		ustaw_kursor (0, 4 + liczba_watkow + nr_watku);
		printf("\033[32mWątek nr: %d, SP: %d, liczba: %d \033[0m\n", nr_watku + 1, i + 1, liczba);
		
		random_wait(max_dlugosc_czekania,min_dlugosc_czekania); // czekanie losowej ilosci czasu
		
		zamknij_mutex(&mutex); // poczatek SK, blokowanie mutexu 
		
		ustaw_kursor (25, 4 + liczba_watkow + nr_watku);
		printf("\033[1;31mWątek nr: %d, SK: %d, liczba: %d \033[0m\n", nr_watku + 1, i + 1, liczba);
		
		/* +1 do liczby */
		counter = liczba;
		counter++;
		
		random_wait(max_dlugosc_czekania,min_dlugosc_czekania);   // czekanie losowej ilosci czasu
		
		liczba = counter;
		
		
		otworz_mutex (&mutex); // koniec SK, otwieranie mutexu przez watek ktory go zamknal
		
		ustaw_kursor (0, 4 + liczba_watkow + nr_watku);
		printf("\033[32mWątek nr: %d, SP: %d, liczba: %d \033[0m\n", nr_watku + 1, i + 1, liczba);
		
		random_wait(max_dlugosc_czekania,min_dlugosc_czekania); // czekaj losową ilość czasu
	}
	
	return 0;
}

int main (int argc, char *argv[]) 
{
	
	// sprawdzenie poprawności arg
	if (argc != 3) 
	{
		printf ("Błąd: niepoprawna liczba argumentów!\n");
		printf ("Wywołaj program wpisując: %s ilość_wątków ilość_sekcji\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	
	liczba_watkow = atoi(argv[1]); // pobieranie liczby watkow z agrumentu pierwszego

	if (liczba_watkow > max_liczba_watkow) // zabezpiecznie przed za duza iloscia watkow
	{
		printf ("Ilość wątków przekracza dozwoloną ilość!\n");
		printf ("Maksymalna dozwolona ilość wątków: %d\n", max_liczba_watkow);
		exit (EXIT_FAILURE);
	}

	liczba_sekcji = atoi(argv[2]); // pobieranie liczby SK z argumentu drugiego
	
	inicjalizuj_mutex (&mutex); // inicjalizowanie mutexu jako otwartego przez NULL -> watki.c
	printf("Zainicjalizowano mutex o adresie %p\n", (void *)&mutex);
	
	liczba = 0;
	
	/* tworzenie watkow */
	for (int i = 0; i < liczba_watkow; i++) 
	{
		
		int *pamiec = malloc (sizeof (int)); // lockowanie pamieci
		*pamiec = i;
		
		//(void *)(&pamiec)!
		
		sleep ((double)i/liczba_watkow);

		watki[i] = utworz_watek (watek_start, (void *)pamiec); // tworzy wątek i przekazuje mu jako argument jego numer !!!!!!
		
		// free((void *)pamiec);
	}
	
	for (int i = 0; i < liczba_watkow; i++) 
	{
		polacz_watek (watki[i]); // użycie dolaczenia watku jako funkcji czekania na zakonczenie watku przez NULL
	}
	
	ustaw_kursor (0, 4 + liczba_watkow * 2);
	
	if (liczba != liczba_watkow * liczba_sekcji) // sprawdzanie powodzenia synchronizacji
	{
		printf ("Synchronizacja nie powiodła się!\nOczekiwano: %d\nOtrzymano: %d\n", (liczba_watkow * liczba_sekcji), liczba);
	} 
	else 
	{
		printf ("Synchronizacja powiodła się!\nOczekiwano: %d\nOtrzymano: %d\n", (liczba_watkow * liczba_sekcji), liczba);
	}
	//free((void *)ppamiec);
	usun_mutex (&mutex); // usuniecie mutexu na sam koniec
	
	return 0;
}