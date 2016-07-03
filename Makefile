NAME=	ft_ls

SRC_C=		main.c

SRC_O=		$(SRC_C:.c=.o)

all: $(NAME)

$(NAME):
	gcc -c srcs/$(SRC_C) -I./includes
	gcc -o $(NAME) $(SRC_O)

clean:
	rm -rf $(SRC_O)

fclean:		clean
	rm -rf $(NAME)

re:		fclean all
