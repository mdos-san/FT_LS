/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:06:10 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 21:56:36 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**
**	This function sort a list of t_dir_container in ascii order
**
*/

void	ft_lstsort(t_list *list, char rev)
{
	t_list	*cursor;
	int		is_not_sorted;
	char	*tmp;
	t_dir_container	*current;
	t_dir_container	*next;

	is_not_sorted = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->next != NULL)
		{
			current = (t_dir_container *)cursor->content;
			next = (t_dir_container *)cursor->next->content;
			if (rev == 0)
			{
				if (ft_strcmp(current->dir_name , next->dir_name) > 0)
				{
					is_not_sorted++;
					tmp = current->dir_name;
					current->dir_name = next->dir_name;
					next->dir_name = tmp;	
				}
			}
			else
			{
				if (ft_strcmp(current->dir_name , next->dir_name) < 0)
				{
					is_not_sorted++;
					tmp = current->dir_name;
					current->dir_name = next->dir_name;
					next->dir_name = tmp;	
				}
			}
		}
		cursor = cursor->next;
	}
	if (is_not_sorted > 0)
		ft_lstsort(list, rev);
}

void	ft_lstsorttime(t_list *list, char rev)
{
	t_list			*cursor;
	int				is_not_sorted;
	char			*tmp;
	t_dir_container	*current;
	t_dir_container	*next;
	struct stat		s_cur;
	struct stat		s_next;

	is_not_sorted = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->next != NULL)
		{
			current = (t_dir_container *)cursor->content;
			next = (t_dir_container *)cursor->next->content;
			(lstat(current->dir_name, &s_cur) == -1) ? ft_putendl("fail") : 0;
			(lstat(next->dir_name, &s_next) == -1) ? ft_putendl("fail") : 0;
			if (rev == 0)
			{
				if (s_cur.st_ctime < s_next.st_ctime)
				{
					is_not_sorted++;
					tmp = current->dir_name;
					current->dir_name = next->dir_name;
					next->dir_name = tmp;	
				}
			}
			else
			{
				if (s_cur.st_ctime > s_next.st_ctime)
				{
					is_not_sorted++;
					tmp = current->dir_name;
					current->dir_name = next->dir_name;
					next->dir_name = tmp;	
				}
			}
		}
		cursor = cursor->next;
	}
	if (is_not_sorted > 0)
		ft_lstsorttime(list, rev);
}
