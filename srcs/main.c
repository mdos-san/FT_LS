#include "ft_ls.h"

t_list	*load_parameters(int ac, char **av)
{
	t_list			*parameters;
	int				nb;
	int				index;
	t_dir_container	container;

	nb = ac;
	index = 2;
	parameters = NULL;
	container.files_names = NULL;
	container.files_types = NULL;
	if (ac >= 2)
	{
		container.dir_name = ft_strdup(av[1]);
		parameters = ft_lstnew(&container, sizeof(t_dir_container));
		nb--;
		while (nb != 1)
		{
			container.dir_name = ft_strdup(av[index]);
			ft_lstadd(&parameters, ft_lstnew(&container, sizeof(t_dir_container)));
			index++;
			nb--;
		}
	}
	else
	{
		container.dir_name = ft_strdup(".");
		parameters = ft_lstnew(&container, sizeof(t_dir_container));
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

void	ft_lstsort(t_list *list, char rev)
{
	t_list	*cursor;
	int		is_not_sorted;
	char	*tmp;
	t_dir_container	*current;
	t_dir_container	*next;

	is_not_sorted = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->next != NULL)
		{
			current = (t_dir_container *)cursor->content;
			next = (t_dir_container *)cursor->next->content;
			if (rev == 0)
			{
				if (ft_strcmp(current->dir_name , next->dir_name) > 0)
				{
					is_not_sorted++;
					tmp = current->dir_name;
					current->dir_name = next->dir_name;
					next->dir_name = tmp;	
				}
			}
			else
			{
				if (ft_strcmp(current->dir_name , next->dir_name) < 0)
				{
					is_not_sorted++;
					tmp = current->dir_name;
					current->dir_name = next->dir_name;
					next->dir_name = tmp;	
				}
			}
		}
		cursor = cursor->next;
	}
	if (is_not_sorted > 0)
		ft_lstsort(list, rev);
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
		value = ((t_dir_container *)list->content)->dir_name;
		if (value[0] == '-')
		{
			if (ft_strchr(value, (int)'a'))
				flags[1]++;
			if (ft_strchr(value, (int)'R'))
				flags[2]++;
			if (ft_strchr(value, (int)'r'))
				flags[3]++;
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
	DIR				*dir_stream;
	struct dirent	*dir_entity;
	char			end;
	t_list			*parameters;
	t_list			*cursor;
	char			*part_path;
	char			*full_path;
	char			flags[5];
	t_dir_container	*d_content;

	parameters = load_parameters(ac, av);
	cursor = parameters;
	parameters = init_flags(flags, cursor);
	cursor = parameters;
	ft_lstsort(parameters, flags[3]);
	while (cursor != NULL)
	{
		d_content = (t_dir_container *)cursor->content;
		if (ac > 2 || flags[2])
		{
			ft_putstr(d_content->dir_name);
			ft_putendl(":");
		}
		end = 0;
		dir_stream = opendir(d_content->dir_name);
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
							ft_putendl("coucou1");
							part_path = ft_strjoin(d_content->dir_name, "/");
							full_path = ft_strjoin(part_path, dir_entity->d_name);
							ft_lstinsert(cursor, ft_lstnew(&(t_dir_container){full_path, NULL, NULL}, sizeof(t_dir_container)));
							ft_strdel(&part_path);
							ft_putendl("coucou2");
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
