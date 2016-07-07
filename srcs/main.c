/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:06:12 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 21:12:55 by mdos-san         ###   ########.fr       */
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
	t_list			*b_files;
	t_list			*b_types;

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
					tmp = ft_lstnew(dir_entity->d_name, ft_strlen(dir_entity->d_name));
					(d_content->files_names == NULL) ? (d_content->files_names = tmp) : (d_content->files_names->next = tmp);
					(d_content->files_names->next != NULL) ? (d_content->files_names = d_content->files_names->next) : (b_files = d_content->files_names);
					tmp = ft_lstnew(&dir_entity->d_type, sizeof(dir_entity->d_type));
					(d_content->files_types == NULL) ? (d_content->files_types = tmp) : (d_content->files_types->next = tmp);
					(d_content->files_types->next != NULL) ? (d_content->files_types = d_content->files_types->next) :  (b_types = d_content->files_types);
/*					if (flags[1] == 1 || dir_entity->d_name[0] != '.')
					{
						ft_putendl(dir_entity->d_name);
						if (flags[2] == 1 && (int)dir_entity->d_type == 4)
						{
							part_path = ft_strjoin(d_content->dir_name, "/");
							full_path = ft_strjoin(part_path, dir_entity->d_name);
							ft_lstinsert(cursor, ft_lstnew(&(t_dir_container){full_path, NULL, NULL}, sizeof(t_dir_container)));
							ft_strdel(&part_path);
						}
					}
*/
				}
				else
					end++;
			}
			d_content->files_names = b_files;
			d_content->files_types = b_types;
			render_files(d_content, flags);
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
