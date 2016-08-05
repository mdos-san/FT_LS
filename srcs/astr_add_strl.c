/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astr_add_strl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:06:48 by mdos-san          #+#    #+#             */
/*   Updated: 2016/08/05 08:06:50 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	astr_add_strl(t_astr *astr, char *str, int free)
{
	astr_add_str(astr, str, free);
	astr_add_str(astr, "\n", 0);
}
