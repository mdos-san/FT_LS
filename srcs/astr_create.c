/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astr_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:03:22 by mdos-san          #+#    #+#             */
/*   Updated: 2016/08/05 08:03:36 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_astr	astr_create(void)
{
	t_astr	astr;

	astr.str = ft_strnew(ASTR_BLOCK_SIZE);
	astr.index = 0;
	astr.nbr_block = 1;
	return (astr);
}
