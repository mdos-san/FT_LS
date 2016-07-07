/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:12:00 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/08 00:40:42 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_date	load_date(int	tmp)
{
	t_date date;

	date.years = tmp * 60 * 60 * 24 * 365;

	return (date);
}

/*
**	This fucntion render the l flag
*/

static void	render_l_flag(t_file *file, char *flags)
{
	struct stat		f_stat;
	struct passwd	*f_pass;
	struct group	*f_grp;
	char			*date;

	stat(file->name, &f_stat);
	(S_ISDIR(f_stat.st_mode)) ? ft_putchar('d') : 0 ;
	(S_ISREG(f_stat.st_mode)) ? ft_putchar('-') : 0 ;
	(S_ISSOCK(f_stat.st_mode)) ? ft_putchar('s') : 0 ;
	(S_ISFIFO(f_stat.st_mode)) ? ft_putchar('p') : 0 ;
	(S_ISCHR(f_stat.st_mode)) ? ft_putchar('c') : 0 ;
	(S_ISCHR(f_stat.st_mode)) ? ft_putchar('c') : 0 ;
	(S_ISBLK(f_stat.st_mode)) ? ft_putchar('b') : 0 ;
	(S_ISLNK(f_stat.st_mode)) ? ft_putchar('l') : 0 ;
	(f_stat.st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(f_stat.st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(f_stat.st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(f_stat.st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(f_stat.st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(f_stat.st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(f_stat.st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(f_stat.st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	(f_stat.st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	ft_putchar(' ');
	ft_putchar(' ');
	ft_putnbr((int)f_stat.st_nlink);
	ft_putchar(' ');
	f_pass = getpwuid(f_stat.st_uid);
	ft_putstr(f_pass->pw_name);
	ft_putchar('\t');
	f_grp = getgrgid(f_stat.st_gid);
	ft_putstr(f_grp->gr_name);
	ft_putchar(' ');
	ft_putnbr(f_stat.st_size);
	ft_putchar('\t');
	date = ctime(&f_stat.st_atime);
	date[16] = '\0';
	ft_putstr(date + 4);
	date[16] = ' ';
	ft_putchar(' ');
	ft_putendl(file->name);
}

/*
**
**	This function have to render files of a dir and take care of flag
**
*/

void	render_files(t_dir_container *dir_content, char *flags)
{
	t_list	*files;
	t_file	*file;

	files = dir_content->files;
	sort_name(files, flags[3]);
	while (files)
	{
		file = (t_file *)files->content;
		if (flags[0] && (file->name[0] != '.' || flags[1]))
			render_l_flag(file, flags);
		else
		{
			if (file->name[0] != '.' || flags[1])
				ft_putendl(file->name);
		}
		files = files->next;
	}
}
