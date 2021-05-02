NAME = a.out

${NAME}:
	gcc 3.c matrix.c

all: ${NAME}

clean:
	rm -rf *.csv

fclean:
	rm -rf *.csv ${NAME}

re: fclean all

.PHONY: all clean fclean re