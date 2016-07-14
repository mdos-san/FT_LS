/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:59:05 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 22:00:41 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**
**
**	This function count the length of a t_list
**
**
*/

int	ft_lstcount(t_list *lst)
{
	t_list	*i;
	int		count;

	count = 0;
	i = lst;
	while (i)
	{
		++count;
		i = i->next;
	}
	return (count);
}
