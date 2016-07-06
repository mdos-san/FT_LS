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

int	main(int ac, char **av)
{
	DIR		*dir_stream;
	struct dirent	*dir_entity;
	char		end;
	t_list		*parameters;
	t_list		*cursor;

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
					ft_putendl(dir_entity->d_name);
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
