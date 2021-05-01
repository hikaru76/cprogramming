CC		:= gcc
SRC		:= check_mylib.c
OBJ		:= check_mylib.o
DEP		:= check_mylib.d
CFLAGS		:= -O2 -Wall -I../include -MP -MMD
LDFLAGS		:= -L../lib -lmatrix
PROGRAM		:= mylib

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

-include $(DEP)

.PHONY: clean
clean:
	rm -f $(OBJ) $(DEP) $(PROGRAM) $(addsuffix .exe,$(PROGRAM))
