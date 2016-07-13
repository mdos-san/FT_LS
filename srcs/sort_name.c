/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:10:36 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 22:37:40 by mdos-san         ###   ########.fr       */
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
	t_list	*current;
	t_list	*next;
	t_file	*tmp;
	t_file	*file;
	t_file	*next_file;

	is_not_sorted = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->next != NULL)
		{
			file = (t_file *)cursor->content;
			next_file = (t_file *)cursor->next->content;
			current = cursor;
			next = cursor->next;
			if (rev == 0)
			{
				if (ft_strcmp(file->name , next_file->name) > 0)
				{
					is_not_sorted++;
					tmp = (t_file*)current->content;
					current->content = next->content;
					next->content = (void *)tmp;	
				}
			}
			else
			{
				if (ft_strcmp(file->name , next_file->name) < 0)
				{
					is_not_sorted++;
					tmp = (t_file*)current->content;
					current->content = next->content;
					next->content = (void *)tmp;	
				}
			}
		}
		cursor = cursor->next;
	}
	if (is_not_sorted > 0)
		sort_name(list, rev);

}

void	sort_nametime(t_list *list, char rev)
{
	t_list	*cursor;
	int		is_not_sorted;
	t_list	*current;
	t_list	*next;
	t_file	*tmp;
	t_file	*file;
	t_file	*next_file;

	is_not_sorted = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->next != NULL)
		{
			file = (t_file *)cursor->content;
			next_file = (t_file *)cursor->next->content;
			current = cursor;
			next = cursor->next;
			if (rev == 0)
			{
				if (file->time < next_file->time)
				{
					is_not_sorted++;
					tmp = (t_file*)current->content;
					current->content = next->content;
					next->content = (void *)tmp;	
				}
			}
			else
			{
				if (file->time > next_file->time)
				{
					is_not_sorted++;
					tmp = (t_file*)current->content;
					current->content = next->content;
					next->content = (void *)tmp;	
				}
			}
		}
		cursor = cursor->next;
	}
	if (is_not_sorted > 0)
		sort_nametime(list, rev);
}
