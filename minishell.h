/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:04:15 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/07 20:56:19 by llacaze          ###   ########.fr       */
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

# define BUFF_SIZE 4
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
	struct s_info	*next;
}					t_info;

int					get_next_line(const int fd, char **line);
t_info				*init_info(void);
t_info				*refresh_info(t_info *info);
t_info				*go_begin(t_info *info);
void				free_info(t_info *info);
char				*get_env(char **env, char *elem);
int					builtin(t_info *info);
void				builtin_env_one(t_info *info);
t_info				*get_env_num(t_info *info, char *elem, char *new_elem);
void				bi_echo(t_info *info);
void				opt_env(t_info *info);
void				bi_setenv(t_info *info);
void				bi_unsetenv(t_info *info);
void				sig_handler(int sig);
void				sig_hand_emp(int sig);

#endif
