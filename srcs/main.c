#include "ft_ls.h"

int	main(int ac, char **av)
{
	DIR		*dir_stream;
	struct dirent	*dir_entity;
	char		end;

	end = 0;
	if (ac >= 2)
		dir_stream = opendir(av[1]);
	else
		dir_stream = opendir(".");
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
	return (0);
}
