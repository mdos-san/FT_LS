#include "ft_ls.h"

/*
**
**	This function create an str that will automaticly reallocate memory if needed;
**
**	struct name is t_astr and contain:
**
**	str : a char * representing the array of char;
**	index : the actual position to write content;
**	nbr_block : The number of blocks allocated to this astr;
**
*/

t_astr	astr_create()
{
	t_astr	astr;

	astr.str = ft_strnew(ASTR_BLOCK_SIZE);
	astr.index = 0;
	astr.nbr_block = 1;
}
