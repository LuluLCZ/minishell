/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:06:03 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/12 16:53:15 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *str, char *command)
{
	char		**tab;
	int			i;
	char		*tmp;
	char		*tmpp;

	i = -1;
	tab = ft_strsplit(str, ':');
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		tmpp = ft_strjoin(tmp, command);
		free(tmp);
		free(tab[i]);
		tab[i] = ft_strdup(tmpp);
		free(tmpp);
		if (access(tab[i], F_OK) == 0)
		{
			tmp = ft_strdup(tab[i]);
			free(tab);
			return (tmp);
		}
	}
	return (NULL);
}

char	*get_env(char **env, char *elem)
{
	char	**str;
	char	*line;

	while (*env)
	{
		str = ft_strsplit(*env, '=');
		if (ft_strcmp(str[0], elem) == 0)
		{
			line = ft_strdup(str[1]);
			free(str);
			return (line);
		}
		env++;
	}
	return ("NULL");
}

t_info		*get_command(t_info *info, char **env, int j)
{
	char	*path;
	int		i;

	i = 0;
	info->line = ft_strtrim(info->line);
	info->line = remove_char(info->line, '\t');
	info->line_tab = ft_strsplit(info->line, ' ');
	path = get_env(env, "PATH");
	info->command = ft_get_path(path, info->line_tab[j]);
	return (info);
}

t_info		*exe(t_info *info, int i)
{
	pid_t	child_pid;

	//on duplique le processus avec fork
	info = get_command(info, info->env, 0);
	if (info->line[0] == '\0')
		return (info);
	if (builtin(info, i) == 1)
		return (info);
	if ((child_pid = fork()) == 0)
	{
		if (info->line_tab[0] != NULL && execve(info->command, info->line_tab, info->env) == -1)
			if (((execve(info->line_tab[0], info->line_tab, info->env) == -1)))
			{
				write(2, "minishell: command not found: ", 31);
				write(2, info->line_tab[0], ft_strlen(info->line_tab[0]));
				write(2, "\n", 1);
				exit(1);
			}
	}
	else if (child_pid != -1)
	{
		signal(SIGINT, sig_handler);
		wait(&child_pid);
	}
	return (info);
}

void	exec_cmd(t_info *info, char **env)
{
	(void)env;
	while (42)
	{
		// info->env = env;
		ft_putstr("\033[0;32m[");
		ft_putstr(get_env(info->env, "USER"));
		ft_putstr("]* \033[0m\033[0;34m*[");
		ft_putstr(get_env(info->env, "PWD"));
		ft_putstr("]\033[0m\xe2\x86\x92\e[31m\xe2\x98\x85\033[0m ");
		signal(SIGINT, sig_hand_emp);
		if (get_next_line(0, &(info->line)) != 0)
			info = exe(info, 0);
	}
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	t_info		*info;

	info = init_info();
	info->env = env;
	info->env_n = env;
	exec_cmd(info, env);
	return (0);
}