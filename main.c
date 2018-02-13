/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:06:03 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/13 20:07:48 by llacaze          ###   ########.fr       */
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
	free(str);
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
			free_tab(tab);
			return (tmp);
		}
	}
	free_tab(tab);
	// ft_strdel(&str);
	return ("NULL");
}

char	*get_env(char **env, char *elem)
{
	char	**str;
	char	*line;
	int		i;

	i = -1;
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
	return ("NULL");
}

t_info		*get_command(t_info *info, char **env, int j)
{
	char	*path;
	int		i;
	char	*tmp;
	i = 0;

	tmp = info->line;
	info->line = ft_strtrim(info->line);
	free(tmp);
	info->line = remove_char(info->line, '\t');
	info->line_tab = ft_strsplit(info->line, ' ');
	path = get_env(env, "PATH");
	info->command = ft_get_path(path, info->line_tab[j]);
	return (info);
}

int			exe(t_info *info, int i)
{
	pid_t	child_pid;
	int		j;
	j = 0;
	//on duplique le processus avec fork
	info = get_command(info, info->env, 0);
	if (info->line[0] == '\0')
		return (0);
	if ((j = builtin(info, i)) == 1 || j == -1)
		return (j);
	if ((child_pid = fork()) == 0)
	{
		if (info->line_tab[0] != NULL && execve(info->command, info->line_tab, info->env) == -1)
		{
			if (((execve(info->line_tab[0], info->line_tab, info->env) == -1)))
			{
				write(2, "minishell: command not found: ", 31);
				write(2, info->line_tab[0], ft_strlen(info->line_tab[0]));
				write(2, "\n", 1);
				exit(1);
			}
		}
	}
	else if (child_pid != -1)
	{
		signal(SIGINT, sig_handler);
		wait(&child_pid);
	}
	free_info(info);
	return (0);
}

void	exec_cmd(t_info *info, char **env)
{
	int		i;
	(void)env;
	char	*tmp;
	char	buf[4096 + 1];

	i = 0;
	while (42)
	{
		tmp = getcwd(buf, 4096);
		ft_putstr("\033[0;32m[\033[0m\033[0;34m*[");
		ft_putstr(tmp);
		ft_putstr("]\033[0m\xe2\x86\x92\e[31m\xe2\x98\x85\033[0m ");
		signal(SIGINT, sig_hand_emp);
		if (get_next_line(0, &(info->line)) != 0)
			i = exe(info, 0);
		if (i == -1)
			break ;
	}
}

int		main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	t_info		*info;
	int			i;

	i = -1;
	info = init_info();
	if (!(info->env = (char **)malloc(sizeof(char *) * 512)))
		return (-1);
	while (env[++i])
		info->env[i] = ft_strdup(env[i]);
	// info->env_n = env;
	exec_cmd(info, env);
	free(info->env);
	free(info->env_n);
	return (0);
}