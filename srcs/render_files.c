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

static void get_right(t_file *file, t_astr *astr, t_view v)
{
	(S_ISDIR(file->stat.st_mode)) ? astr_add_str(astr, "d", 0) : 0 ;
	(S_ISREG(file->stat.st_mode)) ? astr_add_str(astr, "-", 0) : 0 ;
	(S_ISSOCK(file->stat.st_mode)) ? astr_add_str(astr, "s", 0) : 0 ;
	(S_ISFIFO(file->stat.st_mode)) ? astr_add_str(astr, "p", 0) : 0 ;
	(S_ISCHR(file->stat.st_mode)) ? astr_add_str(astr, "c", 0) : 0 ;
	(S_ISCHR(file->stat.st_mode)) ? astr_add_str(astr, "c", 0) : 0 ;
	(S_ISBLK(file->stat.st_mode)) ? astr_add_str(astr, "b", 0) : 0 ;
	(S_ISLNK(file->stat.st_mode)) ? astr_add_str(astr, "l", 0) : 0 ;
	(file->stat.st_mode & S_IRUSR) ? astr_add_str(astr, "r", 0) : astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IWUSR) ? astr_add_str(astr, "w", 0) : astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IXUSR) ? astr_add_str(astr, "x", 0) : astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IRGRP) ? astr_add_str(astr, "r", 0) : astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IWGRP) ? astr_add_str(astr, "w", 0) : astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IXGRP) ? astr_add_str(astr, "x", 0) : astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IROTH) ? astr_add_str(astr, "r", 0) : astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IWOTH) ? astr_add_str(astr, "w", 0) : astr_add_str(astr, "-", 0);
	(file->stat.st_mode & S_IXOTH) ? astr_add_str(astr, "x", 0) : astr_add_str(astr, "-", 0);
	astr_add_str(astr, " ", 0);
	print_col(astr, ft_itoa(file->stat.st_nlink), v.link, 1);
	astr_add_str(astr, ft_itoa((int)file->stat.st_nlink), 1);
	astr_add_str(astr, " ", 0);
}

static void	render_l_flag(t_astr *astr, char *dir, t_file *file, char *flags, t_view v)
{
	char			*date;
	char			*nb;
	char			*col;

	if (flags[0] || file->name[0] != '.') 
	{
		get_right(file, astr, v);
		(file->uid) ? astr_add_str(astr, file->uid->pw_name, 0) : astr_add_str(astr, ft_itoa(file->stat.st_uid), 1);
		(file->uid) ? print_col(astr, file->uid->pw_name, v.usr, 0) : 0;
		astr_add_str(astr, "  ", 0);
		(file->gid) ? astr_add_str(astr, file->gid->gr_name, 0) : astr_add_str(astr, ft_itoa(file->stat.st_gid), 1);
		(file->gid) ? print_col(astr, file->gid->gr_name, v.grp, 0) :0;
		astr_add_str(astr, "  ", 0);
		print_col(astr, ft_itoa(file->stat.st_size), v.size, 1);
		astr_add_str(astr, ft_itoa(file->stat.st_size), 1);
		astr_add_str(astr, " ", 0);
		date = ctime(&file->stat.st_ctime);
		date[16] = '\0';
		astr_add_str(astr, date + 4, 0);
		date[16] = ' ';
		astr_add_str(astr, " ", 0);
		astr_add_str(astr, file->name, 0);
		(S_ISLNK(file->stat.st_mode)) ? read_sym(astr, file->path) : 0 ;
		astr_add_str(astr, "\n", 0);
	}
}

static void	add_dir(t_list *lst, char *path, char *file, int *b)
{
	t_dir_container	dir;
	t_list	*new;
	t_list	*cur;
	int		i;

	i = -1;
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
		while (++i < *b)
			cur = cur->next;
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

static void file_init(t_file *file, t_dir_container *dir_content, t_view *v, int *total)
{
	char			*part;

	part = NULL;
	(ft_strcmp(dir_content->dir_name, "/") == 0)
		? (file->path = ft_strjoin(dir_content->dir_name, file->name))
		: (part = ft_strjoin(dir_content->dir_name, "/"));
	(part != NULL) ? (file->path = ft_strjoin(part, file->name)) : 0;
	lstat(file->path, &file->stat);
	*total += file->stat.st_blocks;
	file->uid = getpwuid(file->stat.st_uid);
	file->gid = getgrgid(file->stat.st_gid);
	(ft_atoi(v->link) < file->stat.st_nlink)
		? (v->link = ft_itoa(file->stat.st_nlink)) : 0;
	(file->uid && ft_strlen(v->usr) < ft_strlen(file->uid->pw_name))
		? (v->usr = ft_strdup(file->uid->pw_name)) : 0;
	(file->gid && ft_strlen(v->grp) < ft_strlen(file->gid->gr_name))
		? (v->grp = ft_strdup(file->gid->gr_name)) : 0;
	(ft_atoi(v->size) < file->stat.st_size)
		? (v->size = ft_itoa(file->stat.st_size)) : 0;
	ft_strdel(&part);
	file->time = (int)file->stat.st_ctime;
}

static void	render_loop(t_astr *astr, t_list *dir, t_dir_container *dir_content, char *flags)
{
	t_list	*files;
	t_file	*file;
	int		add_bool;

	add_bool = 0;
	files = dir_content->files;
	while (files)
	{
		file = (t_file *)files->content;
		if (flags[0] == 1 && (file->name[0] != '.' || flags[1]))
		{
			if (flags[2] && ft_strcmp(file->name, ".") != 0 && ft_strcmp(file->name, "..") != 0)
				(S_ISDIR(file->stat.st_mode)) ? add_dir(dir, file->path, file->name, &add_bool) : 0;
			render_l_flag(astr, dir_content->dir_name, file, flags, dir_content->v);
		}
		else if (file->name[0] != '.' || flags[1])
		{
			if (flags[2])
				(S_ISDIR(file->stat.st_mode)) ? add_dir(dir, file->path, file->name, &add_bool) : 0;
			astr_add_strl(astr, file->name, 0);
		}
		files = files->next;
	}
}

void	render_files(t_astr *astr, t_list *dir, t_dir_container *dir_content, char *flags)
{
	t_list			*files;
	t_file			*file;
	int				total;

	files = dir_content->files;
	total = 0;
	dir_content->v.link = 0;
	dir_content->v.usr = 0;
	dir_content->v.grp = 0;
	dir_content->v.size = 0;
	while (files)
	{
		file = (t_file *)files->content;
		(file->name[0] != '.' || flags[1])
			? file_init(file, dir_content, &dir_content->v, &total)	: 0;
		files = files->next;
	}
	if (flags[0] && total > 0)
	{
		astr_add_str(astr, "total ", 0);
		astr_add_strl(astr, ft_itoa(total), 1);
	}
	files = dir_content->files;
	(flags[4]) ? sort_nametime(files, flags[3]) : sort_name(files, flags[3]);
	render_loop(astr, dir, dir_content, flags);
}
