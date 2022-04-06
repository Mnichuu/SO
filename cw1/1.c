#include <stdio.h>
#include <unistd.h>
 
 
int main(int argc, char const *argv[]) 

{
 
	printf("PID: %d\n", getpid()); // zwraca id procesu
	 
	printf("PPID: %d\n", getppid()); //zwraca id procesu rodzica
	 
	printf("PGID: %d\n", getpgid(getpid())); //zwraca id grupy procesów
	 
	printf("UID: %d\n", getuid());
	 
	printf("GID: %d\n", getgid());
	
	printf("\n");

return 0;
 
}
