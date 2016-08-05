/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:10:36 by mdos-san          #+#    #+#             */
/*   Updated: 2016/08/05 09:36:15 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	basic_sort(t_list *cursor, char rev, int *is_not_sorted)
{
	t_list	*current;
	t_list	*next;
	t_file	*tmp;
	t_file	*file;
	t_file	*next_file;

	file = (t_file *)cursor->content;
	next_file = (t_file *)cursor->next->content;
	current = cursor;
	next = cursor->next;
	if (rev == 0 && (ft_strcmp(file->name, next_file->name) > 0))
	{
		++(*is_not_sorted);
		tmp = (t_file*)current->content;
		current->content = next->content;
		next->content = (void *)tmp;
	}
	else if (rev == 1 && ft_strcmp(file->name, next_file->name) < 0)
	{
		++(*is_not_sorted);
		tmp = (t_file*)current->content;
		current->content = next->content;
		next->content = (void *)tmp;
	}
}

void		sort_name(t_list *list, char rev)
{
	t_list	*cursor;
	int		is_not_sorted;

	is_not_sorted = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->next != NULL)
			basic_sort(cursor, rev, &is_not_sorted);
		cursor = cursor->next;
	}
	(is_not_sorted > 0) ? sort_name(list, rev) : 0;
}

static void	switch_elem(t_list *current, t_list *next, int *is_not_sorted)
{
	t_file	*tmp;

	++(*is_not_sorted);
	tmp = (t_file*)current->content;
	current->content = next->content;
	next->content = (void *)tmp;
}

static void	time_sort(t_list *cursor, char rev, int *is_not_sorted)
{
	t_list	*current;
	t_list	*next;
	t_file	*file;
	t_file	*next_file;

	file = (t_file *)cursor->content;
	next_file = (t_file *)cursor->next->content;
	current = cursor;
	next = cursor->next;
	if (rev == 0 && file->time < next_file->time)
		switch_elem(current, next, is_not_sorted);
	else if (rev == 1 && file->time > next_file->time)
		switch_elem(current, next, is_not_sorted);
	else if (rev == 0 && file->time == next_file->time
			&& ft_strcmp(file->name, next_file->name) > 0)
		switch_elem(current, next, is_not_sorted);
	else if (rev == 1 && file->time == next_file->time
			&& ft_strcmp(file->name, next_file->name) < 0)
		switch_elem(current, next, is_not_sorted);
}

void		sort_nametime(t_list *list, char rev)
{
	t_list	*cursor;
	int		is_not_sorted;

	is_not_sorted = 0;
	cursor = list;
	while (cursor)
	{
		if (cursor->next != NULL)
			time_sort(cursor, rev, &is_not_sorted);
		cursor = cursor->next;
	}
	if (is_not_sorted > 0)
		sort_nametime(list, rev);
}
