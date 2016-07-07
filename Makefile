NAME=		ft_ls

TMP_C=		main.c\
			load_parameters.c\
			ft_lstinsert.c\
			ft_lstsort.c\
			init_flags.c\
			sort_name.c\
			render_files.c\
			ft_lstpushback.c\
			ft_lstcount.c

SRC_C=		$(TMP_C:%=srcs/%)
SRC_O=		$(TMP_C:.c=.o)

all: libft.a includes/libft.h $(NAME)

libft.a:
	make -C libft
	mv libft/libft.a .
	make fclean -C libft

includes/libft.h:
	cp libft/includes/libft.h includes

$(NAME):
	gcc -c $(SRC_C) -I./includes
	gcc -o $(NAME) $(SRC_O) -L. libft.a

clean:
	rm -rf $(SRC_O)

fclean:		clean
	rm -rf $(NAME) libft.a

re:		fclean all
