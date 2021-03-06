/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astr_add_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 07:46:48 by mdos-san          #+#    #+#             */
/*   Updated: 2016/08/05 08:03:06 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	append_str(t_astr *astr, char *str, int index)
{
	ft_strcat(astr->str + astr->index, str);
	astr->index = index;
}

static void	realloc_str(t_astr *astr, char *str, int index)
{
	char	*new;

	astr->nbr_block++;
	new = ft_strnew(ASTR_BLOCK_SIZE * astr->nbr_block);
	ft_strcat(new, astr->str);
	free(astr->str);
	astr->str = new;
	append_str(astr, str, index);
}

void		astr_add_str(t_astr *astr, char *str, int str_free)
{
	int	str_size;

	str_size = ft_strlen(str);
	(astr->index + str_size < astr->nbr_block * ASTR_BLOCK_SIZE)
	? append_str(astr, str, str_size + astr->index)
	: realloc_str(astr, str, str_size + astr->index);
	(str_free == 1) ? free(str) : 0;
}
