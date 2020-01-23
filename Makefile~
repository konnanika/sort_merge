OBJS 		= smj.o parser.o helpers.o unsorted.o sorted.o merged.o
OUT  		= smj
CC   		= gcc
ARGS		= -1 smarelA -2 smarelB

# Compile smj and create executable
all: $(OBJS)
	$(CC) -g $? -o $(OUT)
	rm -f $(OBJS)

smj.o: smj.c
	$(CC) -g -c $?

parser.o: parser.c
	$(CC) -g -c $?

helpers.o: helpers.c
	$(CC) -g -c $?

unsorted.o: unsorted.c
	$(CC) -g -c $?

sorted.o: sorted.c
	$(CC) -g -c $?

parser.o: parser.c
	$(CC) -g -c $?

merged.o: merged.c
	$(CC) -g -c $?

# Run the executable produced
run :
	@$(MAKE) && ./$(OUT) $(ARGS)

# Clear everything
clean:	
	rm -f $(OBJS) $(OUT)
	clear
