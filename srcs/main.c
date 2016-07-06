#include "ft_ls.h"

t_list	*load_parameters(int ac, char **av)
{
	t_list		*parameters;
	int		nb;
	int		index;

	nb = ac;
	index = 2;
	parameters = NULL;
	if (ac >= 2)
	{
		parameters = ft_lstnew(av[1], ft_strlen(av[1]));
		nb--;
		while (nb != 1)
		{
			ft_lstadd(&parameters, ft_lstnew(av[index], ft_strlen(av[index])));
			index++;
			nb--;
		}
	}
	return (parameters);
}

/*
**
**	This function can be added to libft;
**
**	This function insert a new element in a t_list chain;
**
*/

void	ft_lstinsert(t_list *start, t_list *new)
{
	new->next = start->next;
	start->next = new;
}

/*
**	Type of directory is 4;
**	Type of normal file sems to be 8;
**
*/

int	main(int ac, char **av)
{
	DIR		*dir_stream;
	struct dirent	*dir_entity;
	char		end;
	t_list		*parameters;
	t_list		*cursor;
	char		*part_path;
	char		*full_path;

	parameters = load_parameters(ac, av);
	cursor = parameters;
	while (cursor != NULL)
	{
		if (ac > 2)
		{
			ft_putstr(cursor->content);
			ft_putendl(":");
		}
		end = 0;
		dir_stream = opendir((char *)cursor->content);
		if (dir_stream != NULL)
		{
			while (end == 0)
			{
				dir_entity = readdir(dir_stream);
				if (dir_entity != NULL)
				{
					if (dir_entity->d_name[0] != '.')
					{
						ft_putendl(dir_entity->d_name);
						//This part add a new directorie to explore in previtision of -R arg... haha
						if ((int)dir_entity->d_type == 4)
						{
							part_path = ft_strjoin((char*)cursor->content, "/");
							full_path = ft_strjoin(part_path, dir_entity->d_name);
							ft_lstinsert(cursor, ft_lstnew((void *)full_path, ft_strlen(full_path)));
							ft_strdel(&part_path);
							ft_strdel(&full_path);
						}
					}
				}
				else
					end++;
			}
		}
		else
		{
			ft_putendl("An error as occured, errno not used now sorry :P");
		}
		ft_putchar('\n');
		cursor = cursor->next;
	}
	return (0);
}
