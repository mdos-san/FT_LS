/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:12:00 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 21:12:18 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**
**	This function have to render files of a dir and take care of flag
**
*/

void	render_files(t_dir_container *dir_content, char *flags)
{
	t_list	*names;
	t_list	*types;

	names = dir_content->files_names;
	types = dir_content->files_types;
	sort_name(names, flags[3]);
	while (names)
	{
		if (((char *)names->content)[0] != '.' || flags[1])
			ft_putendl((char *)names->content);
		names = names->next;
		types = types->next;
	}
}
