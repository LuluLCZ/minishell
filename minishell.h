/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:04:15 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/20 12:02:20 by llacaze          ###   ########.fr       */
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
t_info				*get_command(t_info *info, char **env, int j);
char				*ft_get_path(char *str, char *command);
int					exe(t_info *info, int i, char *tmp);
char				*new_line(char *str, char *elem, char *new_elem);

#endif
