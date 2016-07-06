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
	else
	{
		parameters = ft_lstnew(".", 1);
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
**
**	This function sort a list in ascii order
**
*/

void	ft_lstsort(t_list *list)
{
	t_list	*cursor;
	int	is_not_sorted;
	char	*tmp;

	is_not_sorted = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->next != NULL)
		{
			if (ft_strcmp((char *)cursor->content, (char *)cursor->next->content) > 0)
			{
				is_not_sorted++;
				tmp = (char *)cursor->content;
				cursor->content = cursor->next->content;
				cursor->next->content = (void *)tmp;	
			}
		}
		cursor = cursor->next;
	}
	if (is_not_sorted > 0)
		ft_lstsort(list);
}

/*
**	This function init flags values
**
**	It return an address representing the new begining of the pile in case flags is first in pile
**	(because flags is removed from the pile)
*/

t_list	*init_flags(char *flags, t_list *list)
{
	char	*value;
	t_list	*previous;
	t_list	*new_begining;

	previous = NULL;
	new_begining = list;
	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	flags[3] = 0;
	flags[4] = 0;
	while (list)
	{
		value = (char *)list->content;
		if (value[0] == '-')
		{
			if (ft_strchr(value, (int)'a'))
				flags[1]++;
			if (ft_strchr(value, (int)'R'))
				flags[2]++;
			if (previous != NULL)
			{
				list = list->next;			
				free(previous->next->content);
				free(previous->next);
				previous->next = list;
			}
			else
			{
				previous = list;
				list = list->next;			
				free(previous->content);
				free(previous);
				previous = NULL;
				new_begining = list;
			}
		}
		else
		{
			previous = list;
			list = list->next;
		}
	}
	if (new_begining == NULL)
		new_begining = ft_lstnew(".", 1);
	return (new_begining);
}

/*
**	Type of directory is 4;
**	Type of normal file sems to be 8;
**
**	When one of the char of flag[5] is set to 1, ft_ls will use the coresponding flag like ls;
**	Description of flag[5];
**
**	flag[0] = -l
**	flag[1] = -a
**	flag[2] = -R
**	flag[3] = -r
**	flag[4] = -t
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
	char		flags[5];

	parameters = load_parameters(ac, av);
	cursor = parameters;
	parameters = init_flags(flags, cursor);
	cursor = parameters;
	ft_lstsort(parameters);
	while (cursor != NULL)
	{
		if (ac > 2 || flags[2])
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
					if (flags[1] == 1 || dir_entity->d_name[0] != '.')
					{
						ft_putendl(dir_entity->d_name);
						if (flags[2] == 1 && (int)dir_entity->d_type == 4)
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
		cursor = cursor->next;
		(cursor != NULL) ? ft_putchar('\n') : 0;
	}
	return (0);
}
