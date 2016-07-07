/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:08:24 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 21:08:47 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
