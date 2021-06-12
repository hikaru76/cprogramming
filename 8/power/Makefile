CC = gcc-11
NAME = power

${NAME}:
		${CC} power.c matrix.c -fopenmp -o ${NAME}

all: ${NAME}

fclean:
	rm -rf ${NAME}

re: fclean all

.PHONY: all fclean re%       