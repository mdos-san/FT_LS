/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 20:57:48 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/08 05:00:46 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**
**	This function load parameters given in prompt
**
*/

t_list	*load_parameters(int ac, char **av)
{
	t_list			*parameters;
	int				nb;
	int				index;
	t_dir_container	container;

	nb = ac;
	index = 2;
	container.files = NULL;
	if (ac >= 2)
	{
		container.dir_name = ft_strdup(av[1]);
		parameters = ft_lstnew(&container, sizeof(t_dir_container));
		while (--nb != 1)
		{
			container.dir_name = ft_strdup(av[index]);
			ft_lstpushback(parameters, ft_lstnew(&container, sizeof(t_dir_container)));
			index++;
		}
	}
	else
	{
		container.dir_name = ft_strdup(".");
		parameters = ft_lstnew(&container, sizeof(t_dir_container));
	}
	return (parameters);
}
