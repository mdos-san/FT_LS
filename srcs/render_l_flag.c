/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_l_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 07:58:04 by mdos-san          #+#    #+#             */
/*   Updated: 2016/08/05 09:05:27 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*print_col(t_astr *astr, char *str, char *max, int col)
{
	int		i;
	int		diff;

	i = 0;
	diff = ft_strlen(max) - ft_strlen(str);
	while (i < diff)
	{
		astr_add_str(astr, " ", 0);
		i++;
	}
	(col) ? free(str) : 0;
	return (str);
}

static void	read_sym(t_astr *astr, char *file)
{
	char	*new;

	new = ft_strnew(1024);
	readlink(file, new, 1024);
	astr_add_str(astr, " -> ", 0);
	astr_add_str(astr, new, 1);
}

static void	get_right_rwx(t_file *file, t_astr *astr)
{
	(file->stat.st_mode & S_IRUSR) ? astr_add_str(astr, "r", 0)
		: astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IWUSR) ? astr_add_str(astr, "w", 0)
		: astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IXUSR) ? astr_add_str(astr, "x", 0)
		: astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IRGRP) ? astr_add_str(astr, "r", 0)
		: astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IWGRP) ? astr_add_str(astr, "w", 0)
		: astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IXGRP) ? astr_add_str(astr, "x", 0)
		: astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IROTH) ? astr_add_str(astr, "r", 0)
		: astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IWOTH) ? astr_add_str(astr, "w", 0)
		: astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IXOTH) ? astr_add_str(astr, "x", 0)
		: astr_add_str(astr, "-", 0);
}

static void	get_right(t_file *file, t_astr *astr, t_view v)
{
	(S_ISDIR(file->stat.st_mode)) ? astr_add_str(astr, "d", 0) : 0;
	(S_ISREG(file->stat.st_mode)) ? astr_add_str(astr, "-", 0) : 0;
	(S_ISSOCK(file->stat.st_mode)) ? astr_add_str(astr, "s", 0) : 0;
	(S_ISFIFO(file->stat.st_mode)) ? astr_add_str(astr, "p", 0) : 0;
	(S_ISCHR(file->stat.st_mode)) ? astr_add_str(astr, "c", 0) : 0;
	(S_ISCHR(file->stat.st_mode)) ? astr_add_str(astr, "c", 0) : 0;
	(S_ISBLK(file->stat.st_mode)) ? astr_add_str(astr, "b", 0) : 0;
	(S_ISLNK(file->stat.st_mode)) ? astr_add_str(astr, "l", 0) : 0;
	get_right_rwx(file, astr);
	astr_add_str(astr, "  ", 0);
	print_col(astr, ft_itoa(file->stat.st_nlink), v.link, 1);
	astr_add_str(astr, ft_itoa((int)file->stat.st_nlink), 1);
	astr_add_str(astr, " ", 0);
}

void		render_l_flag(t_astr *astr, char *dir,
			t_file *file, t_view v)
{
	char			*date;
	char			*nb;
	char			*col;

	get_right(file, astr, v);
	(file->uid) ? astr_add_str(astr, file->uid->pw_name, 0)
		: astr_add_str(astr, ft_itoa(file->stat.st_uid), 1);
	(file->uid) ? print_col(astr, file->uid->pw_name, v.usr, 0) : 0;
	astr_add_str(astr, "  ", 0);
	(file->gid) ? astr_add_str(astr, file->gid->gr_name, 0)
		: astr_add_str(astr, ft_itoa(file->stat.st_gid), 1);
	(file->gid) ? print_col(astr, file->gid->gr_name, v.grp, 0) : 0;
	astr_add_str(astr, "  ", 0);
	print_col(astr, ft_itoa(file->stat.st_size), v.size, 1);
	astr_add_str(astr, ft_itoa(file->stat.st_size), 1);
	astr_add_str(astr, " ", 0);
	date = ctime(&file->stat.st_mtime);
	date[16] = '\0';
	astr_add_str(astr, date + 4, 0);
	date[16] = ' ';
	astr_add_str(astr, " ", 0);
	astr_add_str(astr, file->name, 0);
	(S_ISLNK(file->stat.st_mode)) ? read_sym(astr, file->path) : 0;
	astr_add_str(astr, "\n", 0);
}
