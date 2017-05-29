CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -pedantic -O2 -flto -std=c99

RM = rm -f

VPATH = src

OBJS = main.o

MAIN = tp1

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
