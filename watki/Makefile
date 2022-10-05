#========================================================================
#Autor: Stanisław Mnich,                               Krakow, 7.06.2022
#========================================================================
#
#
# make: all, clean, tar, run8
#
#========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = main
WATKI = 4
SEKCJE = 2
LIB1 = watki

#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
HEADS1 = $(LIB1).h
LIBS1 = $(LIB1).c
#----------------------


#----------------------
#############################
COFLAGS = -pthread -Wall -O -std=c99 -pedantic
LDFLAGS = -pthread -Wall -O -std=c99 -pedantic
LDLIBS = -lpthread

CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXEC2)
#############################
$(EXEC1): $(OBJS1) $(LIBS1)
	 $(LD) -o $@ $(LDFLAGS) $^ $(LDLIBS)
#############################
$(OBJS1): $(HEADS1)
#############################
.PHONY: run8
#############################
run9: $(EXEC1) 
	clear
	./$(EXEC1) $(WATKI) $(SEKCJE)
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
