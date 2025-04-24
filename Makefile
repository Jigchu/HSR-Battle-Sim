main.exe: main.o abilities.o characters.o combat.o core_mechanics.o

main.o: main.c main.h

abilities.o: abilities.c abilities.h

characters.o: characters.c characters.h