/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:20:59 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 21:23:16 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**
**
**	This function add a new element of t_list at the end of the pile
**
**
*/

void	ft_lstpushback(t_list *lst, t_list *new)
{
	t_list	*cursor;

	cursor = lst;
	while (cursor->next)
	{
		cursor = cursor->next;
	}
	cursor->next = new;
}
