CC=gcc
CFLAGS=-c

sql: sql.o read.o queries.o menu.o helpers.o data.o
	$(CC) -pthread sql.o read.o queries.o menu.o helpers.o data.o -o sql -lm

read.o: read.c read.h
	$(CC) $(CFLAGS) read.c

queries.o: queries.c queries.h
	$(CC) $(CFLAGS) queries.c

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) menu.c

helpers.o: helpers.c helpers.h
	$(CC) $(CFLAGS) helpers.c

data.o: data.c data.h
	$(CC) $(CFLAGS) data.c

clean:
	rm *.o sql




# sql.o: sql.c sql.h read.c read.h queries.h queries.c menu.c menu.h helpers.c helpers.h data.c data.h
# 	$(CC) $(CFLAGS) sql.c
