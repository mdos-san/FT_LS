#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <dirent.h>
# include <stdlib.h>

# include "libft.h"

typedef struct	s_dir_container
{
	char		*dir_name;
	t_list		*files;
}				t_dir_container;

typedef struct	s_file
{
	char		*name;
	int			type;
}				t_file;

t_list	*load_parameters(int ac, char **av);
void	ft_lstinsert(t_list *start, t_list *new);
void	ft_lstsort(t_list *list, char rev);
t_list	*init_flags(char *flags, t_list *list);
void	sort_name(t_list *list, char rev);
void	render_files(t_dir_container *dir_content, char *flags);
void	ft_lstpushback(t_list *lst, t_list *new);
int		ft_lstcount(t_list *lst);

#endif
