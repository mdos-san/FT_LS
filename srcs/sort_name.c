/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:10:36 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 21:58:27 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**
**	This function sort file name list by ascii order
**
*/

void	sort_name(t_list *list, char rev)
{
	t_list	*cursor;
	int		is_not_sorted;
	char	*tmp;
	t_list	*current;
	t_list	*next;

	is_not_sorted = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->next != NULL)
		{
			current = cursor;
			next = cursor->next;
			if (rev == 0)
			{
				if (ft_strcmp(current->content , next->content) > 0)
				{
					is_not_sorted++;
					tmp = current->content;
					current->content = next->content;
					next->content = tmp;	
				}
			}
			else
			{
				if (ft_strcmp(current->content , next->content) < 0)
				{
					is_not_sorted++;
					tmp = current->content;
					current->content = next->content;
					next->content = tmp;	
				}
			}
		}
		cursor = cursor->next;
	}
	if (is_not_sorted > 0)
		sort_name(list, rev);

}
