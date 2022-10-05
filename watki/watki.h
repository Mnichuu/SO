#ifndef WATKI_H
#define WATKI_H

#include <pthread.h>

pthread_t utworz_watek (void *funkcja(void *), void *argument); // tworzy nowy wątek, który zacznie wykonywać funkcja i przyjmie argument
void polacz_watek (pthread_t watek); // czekanie na koniec i łączenie wątków
void inicjalizuj_mutex (pthread_mutex_t *mutex);
void zamknij_mutex (pthread_mutex_t *mutex); // zamykanie mutexu = wchodzenie do SK
void otworz_mutex (pthread_mutex_t *mutex); // otwieranie mutexu = wychodzenie z SK
void usun_mutex (pthread_mutex_t *mutex);

#endif