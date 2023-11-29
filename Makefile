CC = g++

FLAGS = -c -Wall

OBJS = main.o container.o guesser.o

Guesser: $(OBJS)
	$(CC) $(OBJS) -o Guesser

container.o: src/container.cpp src/container.h src/color.h
	$(CC) $(FLAGS) src/container.cpp

guesser.o: src/guesser.cpp src/guesser.h src/constants.h src/container.h src/color.h
	$(CC) $(FLAGS) src/guesser.cpp

main.o: src/main.cpp src/container.h src/guesser.h
	$(CC) $(FLAGS) src/main.cpp

clean:
	rm *.o Guesser