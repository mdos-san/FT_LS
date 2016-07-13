#include "ft_ls.h"

/*
**
**	this function just free the str part of an astr
**	astr is normally never allocated.
**
*/

void	astr_delete(t_astr *astr)
{
	(astr->str) ? free(astr->str) : 0;
	astr->str = NULL;
}
