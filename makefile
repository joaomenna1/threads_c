CC = gcc
CFLAGS = -Wall -Wextra -pthread

OBJS = main.o cliente.o fornecedor.o
TARGET = programa_vendedor_kikao

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c cliente.h fornecedor.h
	$(CC) $(CFLAGS) -c main.c

cliente.o: cliente.c cliente.h
	$(CC) $(CFLAGS) -c cliente.c

fornecedor.o: fornecedor.c fornecedor.h
	$(CC) $(CFLAGS) -c fornecedor.c

clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET)
