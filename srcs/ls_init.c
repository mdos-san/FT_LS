#include "ft_ls.h"

t_ls	ls_init(int ac, char **av)
{
	t_ls	ls;

	ls.astr = astr_create();
	ls.parameters = load_parameters(ac, av);
	ls.cursor = ls.parameters;
	ls.parameters = init_flags(ls.flags, ls.cursor);
	(ls.flags[4]) ? ft_lstsorttime(ls.parameters, ls.flags[3]) : ft_lstsort(ls.parameters, ls.flags[3]);
	(ft_lstcount(ls.parameters) >= 2) ? (ls.print_name = 1) : (ls.print_name = 0);
	(ft_lstcount(ls.parameters) == 0) ? (ls.parameters = load_parameters(0, av)) : 0;
	ls.cursor = ls.parameters;
	ls.end = 0;
	return (ls);
}
