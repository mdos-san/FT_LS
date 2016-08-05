/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:08:24 by mdos-san          #+#    #+#             */
/*   Updated: 2016/08/05 08:15:40 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*remove_flags(t_list *list)
{
	t_list	*cursor;
	t_list	*start;
	char	*value;
	char	end;

	end = 0;
	cursor = list;
	start = list;
	while (cursor && end == 0)
	{
		value = ((t_dir_container *)cursor->content)->dir_name;
		if (value[0] == '-')
		{
			start = cursor->next;
			ft_strdel(&value);
			free(cursor->content);
			free(cursor);
			cursor = start;
		}
		else
			end++;
	}
	return (start);
}

static void		var_init(char *flags)
{
	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	flags[3] = 0;
	flags[4] = 0;
}

t_list			*init_flags(char *flags, t_list *list)
{
	char	*value;
	t_list	*cursor;
	char	end;

	end = 0;
	cursor = list;
	var_init(flags);
	while (cursor && end == 0)
	{
		value = ((t_dir_container *)cursor->content)->dir_name;
		if (value[0] == '-')
		{
			(ft_strchr(value, (int)'l')) ? (flags[0] = 1) : 0;
			(ft_strchr(value, (int)'a')) ? (flags[1] = 1) : 0;
			(ft_strchr(value, (int)'R')) ? (flags[2] = 1) : 0;
			(ft_strchr(value, (int)'r')) ? (flags[3] = 1) : 0;
			(ft_strchr(value, (int)'t')) ? (flags[4] = 1) : 0;
		}
		else
			end++;
		cursor = cursor->next;
	}
	return (remove_flags(list));
}
