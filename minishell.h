/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:04:15 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/26 13:39:42 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <sys/types.h>
# include <signal.h>
# include <curses.h>
# include <ncurses.h>
# include <termios.h>

# define BUFF_SIZE 512
# define EOL '\n'

typedef struct		s_info
{
	struct s_info	*prev;
	char			*command;
	char			**line_tab;
	char			**quotes;
	char			*line;
	char			**env;
	int				repl;
	char			**new_en;
	char			**env_n;
	int				do_ret;
	struct s_info	*next;
}					t_info;

int					get_next_line(const int fd, char **line);
t_info				*init_info(void);
t_info				*refresh_info(t_info *info);
t_info				*go_begin(t_info *info);
void				free_info(t_info *info);
char				*get_env(char **env, char *elem);
int					builtin(t_info *info, int i);
void				builtin_env_one(char **env);
t_info				*get_env_num(t_info *info, char *elem, char *new_elem);
void				bi_echo(t_info *info);
void				opt_env(t_info *info);
void				bi_setenv(t_info *info);
void				bi_unsetenv(t_info *info);
void				sig_handler(int sig);
void				sig_hand_emp(int sig);
char				*get_env(char **env, char *elem);
t_info				*get_command(t_info *info, char **env);
char				*ft_get_path(char *str, char *command);
int					exe(t_info *info, int i);
char				*new_line(char *str, char *elem, char *new_elem);
void				env_i(t_info *info);
void				env_equal(t_info *info);
char				**new_env(char **env, char *elem, char
							*new_elem, char *test);
void				usage_setenv(int i, t_info *info, int j, char **tmp);
char				**new_tab(int i, t_info *info, char **tmp);
t_info				*free_get_exe(t_info *info, int i, int line, char **tmp);
void				aff_free(t_info *info, int i, char **tmp);
int					compare(t_info *info, int i, int j);
t_info				*check_i(t_info *info, char **tmp, int i, int line);
void				builtin_env_one(char **env);
t_info				*err_one(t_info *info, int i, char **tmp);
char				*util_get(char *tmp, char **tab, int i);
void				execve_error(t_info *info);
void				exec_cmd(t_info *info);
void				builtin_cd(t_info *info);
int					perm(char *path);
void				error_cd(int i, char *tmp);
void				cd_tild(t_info *info, char *buf);
void				pwd_old_ch(DIR *dir, t_info *info, char *tmp, char *buf);
void				cd_score(t_info *info, char *buf, DIR *dir);
void				cd_dir_nul(char *buf, t_info *info);

#endif
