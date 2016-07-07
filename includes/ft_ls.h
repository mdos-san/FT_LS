#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <dirent.h>
# include <stdlib.h>

# include "libft.h"

typedef struct	s_dir_container
{
	char		*dir_name;
	t_list		*files_names;
	t_list		*files_types;
}				t_dir_container;

t_list	*load_parameters(int ac, char **av);
void	ft_lstinsert(t_list *start, t_list *new);
void	ft_lstsort(t_list *list, char rev);
t_list	*init_flags(char *flags, t_list *list);
void	sort_name(t_list *list, char rev);
void	render_files(t_dir_container *dir_content, char *flags);

#endif
