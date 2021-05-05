# CC			:= gcc-10
# CFLAGS		:= -O2 -Wall -MP -MMD -I../include -DGL_SILENCE_DEPRECATION
# LDFLAGS		:= -L../lib -lmatrix
# SRC			:= draw_curves.c
# OBJS		:= $(patsubst %.c,%.o,$(SRC))
# DEPS		:= $(patsubst %.c,%.d,$(SRC))
# OUTPUT		:= draw_curves

# ifeq ($(shell uname),Darwin)
# FRAMEWORKS	:= -framework OpenGL -framework GLUT
# else
# FRAMEWORKS	:= -lopengl32 -lglu32 -lglut
# endif

# .PHONY: all
# all: $(OUTPUT)

# -include $(DEPS)

# $(OUTPUT): $(OBJS)
# 	$(CC) $^ $(LDFLAGS) $(FRAMEWORKS) -o $@

# %.o: %.c
# 	$(CC) -c $(CFLAGS) $< -o $@

# .PHONY: clean
# clean:
# 	$(RM) -f $(DEPS) $(OBJS) $(OUTPUT) $(addsuffix .exe,$(OUTPUT))

all:
	gcc-10 -O2 -Wall -MP -MMD -I../include -DGL_SILENCE_DEPRECATION -framework OpenGL -framework GLUT draw_curves.c matrix.c

clean:
	rm -rf *.d

fclean: clean
	rm -rf a.out

re: fclean all

.PHONY:
	all clean fclean re