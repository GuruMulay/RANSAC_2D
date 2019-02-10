CC = g++ --std=c++11
CFLAGS = -Wall -c -g -I ./eigen
LFLAGS = -Wall
OBJS = ransac_2d.o ransac.o vector2d.o

all: ransac_2d

ransac_2d: $(OBJS)
	$(CC) $(LFLAGS) ransac_2d.o vector2d.h ransac.h -o ransac_2d

ransac_2d.o: ransac_2d.cpp ransac.h
	$(CC) $(CFLAGS) ransac_2d.cpp

ransac.o: ransac.h vector2d.h
	$(CC) $(CFLAGS) ransac.h

vector2d.o: vector2d.h
	$(CC) $(CFLAFS) vector2d.h

clean:
	-rm *.o *.gch ransac_2d

tar:
	tar -cvf ransac_2d.tar ransac_2d.cpp Makefile eigen
