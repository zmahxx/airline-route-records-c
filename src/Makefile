CC = gcc
CFLAGS = -Wall -g
TARGET = airline

all: $(TARGET)

$(TARGET): main.o route-records.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o route-records.o

main.o: main.c route-records.h
	$(CC) $(CFLAGS) -c main.c

route-records.o: route-records.c route-records.h
	$(CC) $(CFLAGS) -c route-records.c

clean:
	rm -f *.o $(TARGET)
