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

#endif
