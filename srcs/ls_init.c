/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:06:57 by mdos-san          #+#    #+#             */
/*   Updated: 2016/08/05 09:05:47 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	ls_init(int ac, char **av)
{
	t_ls	ls;

	ls.astr = astr_create();
	ls.file_astr = astr_create();
	ls.parameters = load_parameters(ac, av);
	ls.cursor = ls.parameters;
	ls.parameters = init_flags(ls.flags, ls.cursor);
	(ls.flags[4]) ? ft_lstsorttime(ls.parameters, ls.flags[3], NULL)
		: ft_lstsort(ls.parameters, ls.flags[3]);
	ls.print_name = (ft_lstcount(ls.parameters) >= 2) ? 1 : 0;
	(ft_lstcount(ls.parameters) == 0)
		? (ls.parameters = load_parameters(0, av)) : 0;
	ls.cursor = ls.parameters;
	ls.end = 0;
	return (ls);
}
