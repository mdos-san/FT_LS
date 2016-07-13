/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 21:12:00 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/08 06:59:34 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		read_sym(t_astr *astr, char	*file)
{
	char	*new;

	new = ft_strnew(1024);
	readlink(file, new, 1024);
	astr_add_str(astr, " -> ", 0);
	astr_add_str(astr, new, 1);
}

char		*print_col(t_astr *astr, char *str, char* max, int col)
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

/*
 **	This fucntion render the l flag
 */

static void	render_l_flag(t_astr *astr, char *dir, t_file *file, char *flags, t_view v)
{
	struct stat		f_stat;
	struct passwd	*f_pass;
	struct group	*f_grp;
	char			*date;
	char			*nb;
	char			*path;
	char			*part;
	char			*col;

	part = NULL;
	if (flags[0] || file->name[0] != '.') 
	{
		(ft_strcmp(dir, "/") == 0) ? (path = ft_strjoin(dir, file->name)) : (part = ft_strjoin(dir, "/"));
		(ft_strcmp(dir, "/") == 0) ? (path = ft_strjoin(dir, file->name)) : 0 ;
		(part != NULL) ? (path = ft_strjoin(part, file->name)) : 0;
		lstat(path, &f_stat);
		(S_ISDIR(f_stat.st_mode)) ? astr_add_str(astr, "d", 0) : 0 ;
		(S_ISREG(f_stat.st_mode)) ? astr_add_str(astr, "-", 0) : 0 ;
		(S_ISSOCK(f_stat.st_mode)) ? astr_add_str(astr, "s", 0) : 0 ;
		(S_ISFIFO(f_stat.st_mode)) ? astr_add_str(astr, "p", 0) : 0 ;
		(S_ISCHR(f_stat.st_mode)) ? astr_add_str(astr, "c", 0) : 0 ;
		(S_ISCHR(f_stat.st_mode)) ? astr_add_str(astr, "c", 0) : 0 ;
		(S_ISBLK(f_stat.st_mode)) ? astr_add_str(astr, "b", 0) : 0 ;
		(S_ISLNK(f_stat.st_mode)) ? astr_add_str(astr, "l", 0) : 0 ;
		(f_stat.st_mode & S_IRUSR) ? astr_add_str(astr, "r", 0) : astr_add_str(astr, "-", 0);
		(f_stat.st_mode & S_IWUSR) ? astr_add_str(astr, "w", 0) : astr_add_str(astr, "-", 0);
		(f_stat.st_mode & S_IXUSR) ? astr_add_str(astr, "x", 0) : astr_add_str(astr, "-", 0);
		(f_stat.st_mode & S_IRGRP) ? astr_add_str(astr, "r", 0) : astr_add_str(astr, "-", 0);
		(f_stat.st_mode & S_IWGRP) ? astr_add_str(astr, "w", 0) : astr_add_str(astr, "-", 0);
		(f_stat.st_mode & S_IXGRP) ? astr_add_str(astr, "x", 0) : astr_add_str(astr, "-", 0);
		(f_stat.st_mode & S_IROTH) ? astr_add_str(astr, "r", 0) : astr_add_str(astr, "-", 0);
		(f_stat.st_mode & S_IWOTH) ? astr_add_str(astr, "w", 0) : astr_add_str(astr, "-", 0);
		(f_stat.st_mode & S_IXOTH) ? astr_add_str(astr, "x", 0) : astr_add_str(astr, "-", 0);
		astr_add_str(astr, " ", 0);
		print_col(astr, ft_itoa(f_stat.st_nlink), v.link, 1);
		astr_add_str(astr, ft_itoa((int)f_stat.st_nlink), 1);
		astr_add_str(astr, " ", 0);
		f_pass = getpwuid(f_stat.st_uid);
		(f_pass) ? astr_add_str(astr, f_pass->pw_name, 0) : astr_add_str(astr, ft_itoa(f_stat.st_uid), 1);
		(f_pass) ? print_col(astr, f_pass->pw_name, v.usr, 0) : 0;
		astr_add_str(astr, "  ", 0);
		f_grp = getgrgid(f_stat.st_gid);
		(f_grp) ? astr_add_str(astr, f_grp->gr_name, 0) : astr_add_str(astr, ft_itoa(f_stat.st_gid), 1);
		(f_grp) ? print_col(astr, f_grp->gr_name, v.grp, 0) :0;
		astr_add_str(astr, "  ", 0);
		print_col(astr, ft_itoa(f_stat.st_size), v.size, 1);
		astr_add_str(astr, ft_itoa(f_stat.st_size), 1);
		astr_add_str(astr, " ", 0);
		date = ctime(&f_stat.st_ctime);
		date[16] = '\0';
		astr_add_str(astr, date + 4, 0);
		date[16] = ' ';
		astr_add_str(astr, " ", 0);
		astr_add_str(astr, file->name, 0);
		(S_ISLNK(f_stat.st_mode)) ? read_sym(astr, path) : 0 ;
		astr_add_str(astr, "\n", 0);
		part = NULL;
	}
}

static void	add_dir(t_list *lst, char *path, char *file, int	*b)
{
	t_dir_container	dir;
	t_list	*new;
	t_list	*cur;
	int		i;

	i = 0;
	dir.dir_name = ft_strdup(path);
	dir.files = NULL;
	cur = lst;
	new = ft_lstnew(&dir, sizeof(t_dir_container));
	if (*b == 0)
	{
		(lst->next != NULL) ? (new->next = lst->next) : (lst->next = new);
		lst->next = new;
		*b += 1;
	}
	else
	{
		while (i < *b)
		{
			cur = cur->next;
			i++;
		}
		(cur->next != NULL) ? (new->next = cur->next) : (cur->next = new);
		cur->next = new;
		*b += 1;
	}
}

/*
 **
 **	This function have to render files of a dir and take care of flag
 **
 */

void	render_files(t_astr *astr, t_list *dir, t_dir_container *dir_content, char *flags)
{
	t_list			*files;
	t_file			*file;
	struct stat		f_stat;
	int				total;
	t_view			v;
	char			*path;
	char			*part;
	struct passwd	*f_pass;
	struct group	*f_grp;
	int				add_bool;

	files = dir_content->files;
	total = 0;
	v.link = 0;
	v.usr = 0;
	v.grp = 0;
	v.size = 0;
	part = NULL;
	add_bool = 0;
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
			(f_pass && ft_strlen(v.usr) < ft_strlen(f_pass->pw_name)) ? (v.usr = ft_strdup(f_pass->pw_name)) : 0;
			(f_grp && ft_strlen(v.grp) < ft_strlen(f_grp->gr_name)) ? (v.grp = ft_strdup(f_grp->gr_name)) : 0;
			(ft_atoi(v.size) < f_stat.st_size) ? (v.size = ft_itoa(f_stat.st_size)) : 0;
			ft_strdel(&path);
			ft_strdel(&part);
			file->time = (int)f_stat.st_ctime;
			part = NULL;
		}
		files = files->next;
	}
	if (flags[0] && total > 0)
	{
		astr_add_str(astr, "total ", 0);
		astr_add_str(astr, ft_itoa(total), 1);
		astr_add_str(astr, "\n", 0);
	}
	files = dir_content->files;
	(flags[4]) ? sort_nametime(files, flags[3]) : sort_name(files, flags[3]);
	while (files)
	{
		file = (t_file *)files->content;
		if (flags[0] == 1 && (file->name[0] != '.' || flags[1]))
		{
			(ft_strcmp(dir_content->dir_name, "/") == 0) ? (path = ft_strjoin(dir_content->dir_name, file->name)) : (part = ft_strjoin(dir_content->dir_name, "/"));
			(part != NULL) ? (path = ft_strjoin(part, file->name)) : 0;
			lstat(path, &f_stat);
			if (flags[2] && ft_strcmp(file->name, ".") != 0 && ft_strcmp(file->name, "..") != 0)
				(S_ISDIR(f_stat.st_mode)) ? add_dir(dir, path, file->name, &add_bool) : 0;
			render_l_flag(astr, dir_content->dir_name, file, flags, v);
		}
		else
		{
			(ft_strcmp(dir_content->dir_name, "/") == 0) ? (path = ft_strjoin(dir_content->dir_name, file->name)) : (part = ft_strjoin(dir_content->dir_name, "/"));
			(part != NULL) ? (path = ft_strjoin(part, file->name)) : 0;
			lstat(path, &f_stat);
			if (file->name[0] != '.' || flags[1])
			{
				if (flags[2])
					(S_ISDIR(f_stat.st_mode)) ? add_dir(dir, path, file->name, &add_bool) : 0;
				astr_add_str(astr, file->name, 0);
				astr_add_str(astr, "\n", 0);
			}
			ft_strdel(&part);
			ft_strdel(&path);
		}
		files = files->next;
	}
}
