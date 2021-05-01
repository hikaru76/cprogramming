CC			:= gcc
AR			:= ar rv
CFLAGS		:= -O2 -Wall -MP -MMD -I../include -DGL_SILENCE_DEPRECATION
LDFLAGS		:= -L../lib -lmatrix
SRC			:= check_lagrange.c lagrange.c
HDR			:= lagrange.h
OBJS		:= $(patsubst %.c,%.o,$(SRC))
DEPS		:= $(patsubst %.c,%.d,$(SRC))
OUTPUT		:= lagrange

ifeq ($(shell uname),Darwin)
FRAMEWORKS	:= -framework OpenGL -framework GLUT
else
FRAMEWORKS	:= -lopengl32 -lglu32 -lglut
endif

.PHONY: all
all: $(OUTPUT)

-include $(DEPS)

$(OUTPUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(FRAMEWORKS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) -f $(DEPS) $(OBJS) $(OUTPUT) $(addsuffix .exe,$(OUTPUT))
