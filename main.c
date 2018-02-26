/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:06:03 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/26 13:39:10 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_get_path(char *str, char *command)
{
	char		**tab;
	int			i;
	char		*tmp;
	char		*tmpp;

	i = -1;
	tab = ft_strsplit(str, ':');
	while (tab[++i] != NULL)
	{
		tmp = ft_strjoin(tab[i], "/");
		tmpp = ft_strjoin(tmp, command);
		ft_strdel(&tab[i]);
		tab[i] = ft_strdup(tmpp);
		ft_strdel(&tmpp);
		if (access(tab[i], F_OK) == 0)
		{
			tmp = util_get(tmp, tab, i);
			return (tmp);
		}
		free(tmp);
		free(tmpp);
	}
	free_tab(tab);
	return (ft_strdup("NULL"));
}

char		*get_env(char **env, char *elem)
{
	char	**str;
	char	*line;
	int		i;

	i = -1;
	if (env && env[0])
		while (*env)
		{
			str = ft_strsplit(*env, '=');
			if (ft_strcmp(str[0], elem) == 0)
			{
				line = ft_strdup(str[1]);
				free_tab(str);
				return (line);
			}
			env++;
			free_tab(str);
		}
	return (ft_strdup("NULL"));
}

t_info		*get_command(t_info *info, char **env)
{
	char	*path;
	char	*tmpo;

	tmpo = ft_strtrim(info->line);
	free(info->line);
	info->line = ft_strdup(tmpo);
	free(tmpo);
	info->line = remove_char(info->line, '\t');
	info->line_tab = ft_strsplit(info->line, ' ');
	path = get_env(env, "PATH");
	info->command = ft_get_path(path, info->line_tab[0]);
	free(path);
	return (info);
}

int			exe(t_info *info, int i)
{
	pid_t	child_pid;

	if (info->line[0] == '\0')
	{
		free(info->line);
		return (0);
	}
	info = get_command(info, info->env);
	if (builtin(info, i) == 1)
	{
		free_info(info);
		return (0);
	}
	if ((child_pid = fork()) == 0)
		execve_error(info);
	else if (child_pid != -1)
	{
		signal(SIGINT, sig_handler);
		wait(&child_pid);
	}
	(i != 5 && i != 4) ? free_info(info) : 0;
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_info		*info;
	int			i;

	(void)av;
	(void)ac;
	i = -1;
	info = init_info();
	if (!(info->env = (char **)malloc(sizeof(char *) * 512)))
		return (-1);
	while (env[++i])
		info->env[i] = ft_strdup(env[i]);
	info->env[i] = NULL;
	exec_cmd(info);
	return (0);
}
