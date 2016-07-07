/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:12:00 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 23:06:24 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	This fucntion render the l flag
*/

static void	render_l_flag(t_file *file, char *flags)
{
	ft_putendl(file->name);
}

/*
**
**	This function have to render files of a dir and take care of flag
**
*/

void	render_files(t_dir_container *dir_content, char *flags)
{
	t_list	*files;
	t_file	*file;

	files = dir_content->files;
	sort_name(files, flags[3]);
	while (files)
	{
		file = (t_file *)files->content;
		if (flags[0])
			render_l_flag(file, flags);
		else
		{
			if (file->name[0] != '.' || flags[1])
				ft_putendl(file->name);
		}
		files = files->next;
	}
}
