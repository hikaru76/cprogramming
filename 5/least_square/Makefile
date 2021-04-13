CC			:= gcc
CFLAGS		:= -O2 -Wall -MP -MMD -I../include -DGL_SILENCE_DEPRECATION
LDFLAGS		:= -L../lib -lmatrix
SRC			:= check_least_square.c least_square.c
OBJ			:= $(patsubst %.c,%.o,$(SRC))
DEP			:= $(patsubst %.c,%.d,$(SRC))
OUTPUT		:= least_square

ifeq ($(shell uname),Darwin)
FRAMEWORKS	:= -framework OpenGL -framework GLUT
else
FRAMEWORKS	:= -lopengl32 -lglu32 -lglut
endif

.PHONY: all
all: $(OUTPUT)

-include $(DEP)

$(OUTPUT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(FRAMEWORKS) 

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) -f *.o *.d $(OUTPUT) $(addsuffix .exe,$(OUTPUT))
