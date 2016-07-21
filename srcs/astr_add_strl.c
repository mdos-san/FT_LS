#include "ft_ls.h"

void	astr_add_strl(t_astr *astr, char *str, int free)
{
	astr_add_str(astr, str, free);
	astr_add_str(astr, "\n", 0);
}
