/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:12:00 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/08 04:08:54 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*print_col(char *str, char* max, int col)
{
	int		i;
	int		diff;

	i = 0;
	diff = ft_strlen(max) - ft_strlen(str);
	while (i < diff)
	{
		ft_putchar(' ');
		i++;
	}
	return (str);
}

/*
 **	This fucntion render the l flag
 */

static void	render_l_flag(char *dir, t_file *file, char *flags, t_view v)
{
	struct stat		f_stat;
	struct passwd	*f_pass;
	struct group	*f_grp;
	char			*date;
	char			*nb;
	int				ret;
	char			*path;
	char			*part;
	char			*col;

	part = NULL;
	if (flags[0] || file->name[0] != '.') 
	{
		(ft_strcmp(dir, "/") == 0) ? (path = ft_strjoin(dir, file->name)) : 0 ;
		(part != NULL) ? (path = ft_strjoin(part, file->name)) : 0;
		(path == NULL) ? ft_putendl("coucou") : 0;
		lstat(path, &f_stat);
		(ret == -1) ? ft_putendl("error") : 0;
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
		ft_putstr("  ");
		print_col(ft_itoa(f_stat.st_nlink), v.link, 1);
		ft_putnbr((int)f_stat.st_nlink);
		ft_putchar(' ');
		f_pass = getpwuid(f_stat.st_uid);
		ft_putstr(f_pass->pw_name);
		print_col(f_pass->pw_name, v.usr, 2);
		ft_putstr("  ");
		f_grp = getgrgid(f_stat.st_gid);
		ft_putstr(f_grp->gr_name);
		print_col(f_grp->gr_name, v.grp, 3);
		ft_putstr("  ");
		print_col(ft_itoa(f_stat.st_size), v.size, 4);
		ft_putnbr(f_stat.st_size);
		ft_putchar(' ');
		date = ctime(&f_stat.st_atime);
		date[16] = '\0';
		ft_putstr(date + 4);
		date[16] = ' ';
		ft_putchar(' ');
		ft_putendl(file->name);
		part = NULL;
	}
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
	struct stat		f_stat;
	int		total;
	t_view	v;
	char	*path;
	char	*part;
	struct passwd	*f_pass;
	struct group	*f_grp;

	files = dir_content->files;
	sort_name(files, flags[3]);
	total = 0;
	v.link = 0;
	v.usr = 0;
	v.grp = 0;
	v.size = 0;
	part = NULL;
	while (files)
	{
		file = (t_file *)files->content;
		if (file->name[0] != '.' || flags[1])
		{
			(ft_strcmp(dir_content->dir_name, "/") == 0) ? (path = ft_strjoin(dir_content->dir_name, file->name)) : (part = ft_strjoin(dir_content->dir_name, "/"));
			(part != NULL) ? (path = ft_strjoin(part, file->name)) : 0;
			lstat(path, &f_stat);
			total += f_stat.st_blocks;
			f_pass = getpwuid(f_stat.st_uid);
			f_grp = getgrgid(f_stat.st_gid);
			(ft_atoi(v.link) < f_stat.st_nlink) ? (v.link = ft_itoa(f_stat.st_nlink)) : 0;
			(ft_strlen(v.usr) < ft_strlen(f_pass->pw_name)) ? (v.usr = ft_strdup(f_pass->pw_name)) : 0;
			(ft_strlen(v.grp) < ft_strlen(f_grp->gr_name)) ? (v.grp = ft_strdup(f_grp->gr_name)) : 0;
			(ft_atoi(v.size) < f_stat.st_size) ? (v.size = ft_itoa(f_stat.st_size)) : 0;
			ft_strdel(&path);
			ft_strdel(&part);
			part = NULL;
		}
		files = files->next;
	}
	if (flags[0])
	{
		ft_putstr("total ");
		ft_putendl(ft_itoa(total));
	}
	files = dir_content->files;
	while (files)
	{
		file = (t_file *)files->content;
		if (flags[0] == 1 && (file->name[0] != '.' || flags[1]))
			render_l_flag(dir_content->dir_name, file, flags, v);
		else
		{
			if (file->name[0] != '.' || flags[1])
				ft_putendl(file->name);
		}
		files = files->next;
	}
}
