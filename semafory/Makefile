#========================================================================
#Autor: Stanisław Mnich,                               Krakow, 30.05.2022
#========================================================================
#
#
# make: all, clean, tar, run
#
#========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = powielacz
NAME2 = sumator
BIB = semafor
PLIK_WE_WY = numer.txt
L_PROC = 3
L_SEK = 2
SEMAFOR = /sem_powielacz
SYNCHRO = 1

#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
#----------------------
BIBS = $(BIB).c
#----------------------


#----------------------
#############################
COFLAGS = -pthread -Wall -O -std=c99 -pedantic
LDFLAGS = -pthread -Wall -O -std=c99 -pedantic

CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXEC2)
#############################
$(EXEC1): $(OBJS1) $(BIBS)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2) $(BIBS)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: run
#############################
run: $(EXEC1) $(EXEC2)
	./$(EXEC1) $(EXEC2) $(L_PROC) $(L_SEK) $(PLIK_WE_WY) $(SEMAFOR) $(SYNCHRO)
	@echo "\n=========================\n"
#############################
.PHONY: clean tar
clean:                                                     
	
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
