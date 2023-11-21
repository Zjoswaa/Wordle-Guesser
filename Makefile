CC = g++

FLAGS = -c -Wall

OBJS = main.o container.o guesser.o

Guesser: $(OBJS)
	$(CC) $(OBJS) -o Guesser

container.o: container.cpp container.h color.h
	$(CC) $(FLAGS) container.cpp

guesser.o: guesser.cpp guesser.h constants.h container.h color.h
	$(CC) $(FLAGS) guesser.cpp

main.o: main.cpp container.h guesser.h
	$(CC) $(FLAGS) main.cpp

clean:
	rm *.o ./Guesser