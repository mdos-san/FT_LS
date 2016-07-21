#include "ft_ls.h"

void	ls_start(t_ls *ls)
{
	while (ls->cursor != NULL)
	{
		ls->d_content = (t_dir_container *)ls->cursor->content;
		ls->dir_stream = opendir(ls->d_content->dir_name);
		if (ls->dir_stream != NULL)
		{
			if (ls->print_name || (ls->flags[2] && ls->end == 1))
			{
				astr_add_str(&ls->astr, ls->d_content->dir_name, 0);
				astr_add_str(&ls->astr, ":\n", 0);
			}
			ls->end = 0;
			while (ls->end == 0)
			{
				ls->dir_entity = readdir(ls->dir_stream);
				if (ls->dir_entity != NULL)
				{
					ls->file.name = ft_strdup(ls->dir_entity->d_name);
					ls->file.type = 0;
					ls->tmp = ft_lstnew(&ls->file, sizeof(t_file));
					(ls->d_content->files == NULL) ? (ls->d_content->files = ls->tmp) : ft_lstpushback(ls->d_content->files, ls->tmp);
				}
				else
					ls->end++;
			}
			render_files(&ls->astr, ls->cursor, ls->d_content, ls->flags);
			closedir(ls->dir_stream);
		}
		else
		{
			if (lstat(ls->d_content->dir_name, &ls->buf) == -1)
			{
				ls->error = ft_strjoin("ft_ls: ", ls->d_content->dir_name);
				perror(ls->error);
				ft_strdel(&ls->error);
			}
			else
			{
				astr_add_str(&ls->astr, ls->d_content->dir_name, 0);
				astr_add_str(&ls->astr, "\n", 0);
			}
		}
		ls->cursor = ls->cursor->next;
		(ls->cursor != NULL) ? astr_add_str(&ls->astr, "\n", 0) : 0;
	}
	ft_putstr(ls->astr.str);
}
