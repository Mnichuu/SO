#ifndef SEMAFOR_H
#define SEMAFOR_H

sem_t *stworz_semafor(const char *name);
sem_t *otworz_semafor(const char *name);
void otrzymaj_wartosc_semafora(sem_t *sem, int *sval);
void podnies_semafor(sem_t *sem);
void opusc_semafor(sem_t *sem);
void zamknij_semafor(sem_t *sem);
void usun_semafor(const char *name);

#endif