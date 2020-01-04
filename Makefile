but : Snake

OFILES = snake.o \
		 pastille.o \
		 timer.o \
		 tail.o \
		 Main.o

CC = gcc

CFLAGS =  -lgraph


#DEPENDANCES

snake.o : snake.h 

tail.o : tail.h 

pastille.o : pastille.h

timer.o : timer.h

Main.o : snake.h tail.h pastille.h timer.h


#CHAPITRE 4 : DEPENDANCES AVEC COMMANDES
Snake : $(OFILES)
	    $(CC) $(CFLAGS) -o Snake $(OFILES)

clean : 
		-rem $(OFILES) Snake

run : 
	./Snake

.PHONY : but clean