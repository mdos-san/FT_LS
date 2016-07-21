/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 00:13:59 by mdos-san          #+#    #+#             */
/*   Updated: 2016/07/08 07:04:00 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <stdlib.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

# include <stdio.h>

# include "libft.h"

# define ASTR_BLOCK_SIZE 501200

typedef struct	s_view
{
	char*		link;
	char		*usr;
	char		*grp;
	char*		size;
}				t_view;

typedef struct	s_dir_container
{
	char		*dir_name;
	t_list		*files;
	t_view		v;
}				t_dir_container;

typedef struct	s_file
{
	char			*name;
	char			*path;
	int				type;
	int				time;
	struct stat		stat;
	struct passwd	*uid;
	struct group	*gid;

}				t_file;

typedef struct	s_date
{
	int			years;
	char		months[3];
	int			days;
	int			hours;
	int			mins;
	int			sec;
}				t_date;

typedef struct	s_astr
{
	char		*str;
	int			index;
	int			nbr_block;
}				t_astr;

typedef struct	s_ls
{
	DIR				*dir_stream;
	struct dirent	*dir_entity;
	char			end;
	t_list			*parameters;
	t_list			*cursor;
	char			*part_path;
	char			*full_path;
	char			flags[5];
	t_dir_container	*d_content;
	t_list			*tmp;
	t_file			file;
	char			print_name;
	char			*error;
	struct stat		buf;
	t_astr			astr;
}				t_ls;

t_ls			ls_init(int ac, char **av);
void			ls_start(t_ls *ls);
t_list			*load_parameters(int ac, char **av);
void			ft_lstinsert(t_list *start, t_list *new);
void			ft_lstsort(t_list *list, char rev);
void			ft_lstsorttime(t_list *list, char rev);
t_list			*init_flags(char *flags, t_list *list);
void			sort_name(t_list *list, char rev);
void			render_files(t_astr *astr, t_list *dir, t_dir_container *dir_content, char *flags);
void			ft_lstpushback(t_list *lst, t_list *new);
int				ft_lstcount(t_list *lst);
t_astr			astr_create();
void			astr_delete(t_astr *astr);
void			astr_add_str(t_astr *astr, char *str, int free);
void			sort_nametime(t_list *list, char rev);
void			render_l_flag(t_astr *astr, char *dir, t_file *file, char *flags, t_view v);


#endif
