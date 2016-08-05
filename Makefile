NAME=		ft_ls

FLAGS=		-Werror -Wextra -Wall

TMP_C=		main.c\
			ls_init.c\
			ls_start.c\
			load_parameters.c\
			ft_lstinsert.c\
			ft_lstsort.c\
			init_flags.c\
			sort_name.c\
			render_files.c\
			render_l_flag.c\
			ft_lstpushback.c\
			ft_lstcount.c\
			astr_create.c\
			astr_delete.c\
			astr_add_str.c\
			astr_add_strl.c

SRC_C=		$(TMP_C:%=srcs/%)
SRC_O=		$(TMP_C:.c=.o)

all: libft.a includes/libft.h $(SRC_O) $(NAME)

libft.a:
	make -C libft
	mv libft/libft.a .
	make fclean -C libft

includes/libft.h:
	cp libft/includes/libft.h includes

%.o: srcs/%.c
	gcc -c $< -I./includes $(FLAGS)

$(NAME):
	gcc -o $(NAME) $(FLAGS) $(SRC_O) -L. libft.a

clean:
	rm -rf $(SRC_O)

fclean:		clean
	rm -rf $(NAME) libft.a

re:		fclean all
