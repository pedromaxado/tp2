CC = gcc

CFLAGS = -Iheaders -g -Wall -Wextra -Werror -pedantic -std=c99

RM = rm -f

VPATH = src

OBJS = main.o inverted_index.o file_handler.o internal_sort.o external_sort.o

MAIN = tp2

$(MAIN): $(OBJS)
	@echo ""
	@echo " --- COMPILANDO PROGRAMA ---"
	@$(CC) $(CFLAGS) $(OBJS) -o $(MAIN)
	@echo ""

%.o: %.c %.h
	@echo " --- COMPILANDO OBJETO \"$@\""
	@$(CC) $(CFLAGS) $< -c

clean:
	$(RM) *.o *.gch

run: $(MAIN)
	./$(MAIN)
