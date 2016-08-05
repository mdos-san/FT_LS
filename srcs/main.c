/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:06:12 by mdos-san          #+#    #+#             */
/*   Updated: 2016/08/05 08:04:08 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	t_ls	ls;

	ls = ls_init(ac, av);
	ls_start(&ls);
	astr_delete(&ls.file_astr);
	astr_delete(&ls.astr);
	return (0);
}
