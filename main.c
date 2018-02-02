/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:06:03 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/02 20:57:47 by llacaze          ###   ########.fr       */
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
		i++;
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

t_info		*get_command(t_info *info, char **env)
{
	char	*path;

	info->line_tab = ft_strsplit(info->line, ' ');
	path = get_env(env, "PATH");
	info->command = ft_get_path(path, info->line_tab[0]);
	return (info);
}

t_info		*exe(t_info *info)
{
	pid_t	child_pid;

	//on duplique le processus avec fork
	info = get_command(info, info->env);
	if (builtin(info) == 1)
		return (info);
	child_pid = fork();
	if (child_pid < 0)
		perror("fork");
	else if (child_pid == 0)
	{
		execve(info->command, info->line_tab, info->env);
	}
	wait(&child_pid);
	return (info);
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	t_info		*info;

	info = init_info();
	info->env = env;
	while (42)
	{
		ft_putstr("\033[1;31m[");
		ft_putstr(get_env(info->env, "PWD"));
		ft_putstr("]\t\033[1;36m8\033[0m\033[0;35m======\033[0m\033[1;31m=>\033[0m");
		if (get_next_line(0, &(info->line)) != 0)
			info = exe(info);
	}
	return (0);
}