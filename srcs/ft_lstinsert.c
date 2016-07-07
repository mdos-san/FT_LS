/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:04:43 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/07 21:05:10 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**
**	This function can be added to libft;
**
**	This function insert a new element in a t_list chain;
**
*/

void	ft_lstinsert(t_list *start, t_list *new)
{
	new->next = start->next;
	start->next = new;
}
