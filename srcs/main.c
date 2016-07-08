/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:06:12 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/08 07:24:02 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	t_list			*tmp;
	t_file			file;
	char			print_name;
	char			*error;

	parameters = load_parameters(ac, av);
	cursor = parameters;
	parameters = init_flags(flags, cursor);
	ft_lstsort(parameters, flags[3]);
	(ft_lstcount(parameters) >= 2) ? (print_name = 1) : (print_name = 0);
	(ft_lstcount(parameters) == 0) ? (parameters = load_parameters(0, av)) : 0 ;
	cursor = parameters;
	end = 0;
	while (cursor != NULL)
	{
		d_content = (t_dir_container *)cursor->content;
		if (print_name || (flags[2] && end == 1))
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
					file.name = ft_strdup(dir_entity->d_name);
					file.type = 0;
					tmp = ft_lstnew(&file, sizeof(t_file));
					(d_content->files == NULL) ? (d_content->files = tmp) : ft_lstpushback(d_content->files, tmp);
				}
				else
					end++;
			}
			render_files(cursor, d_content, flags);
			closedir(dir_stream);
		}
		else
		{
			error = ft_strjoin("ft_ls: ", d_content->dir_name);
			perror(error);
			ft_strdel(&error);
		}
		cursor = cursor->next;
		(cursor != NULL) ? ft_putchar('\n') : 0;
	}
	return (0);
}
