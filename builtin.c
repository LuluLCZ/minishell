/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:42:43 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/24 19:15:03 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*pwd_cwd(char *str)
{
	char	*new_str;
	int		j;
	int		i;

	i = 0;
	while (*str)
		if (*str++ == ' ')
			i++;
	new_str = ft_strnew(ft_strlen(str) + i + 2);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			new_str[j] = '\\';
			j++;
		}
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int			perm(char *path)
{
	struct stat		fstat;
	int				i;

	if (stat(path, &fstat) == -1)
		i = -1;
	else
		i = ((fstat.st_mode & S_IRGRP) ? 1 : 0);
	return (i);
}

int			builtin(t_info *info, int i)
{
	(void)i;
	if (info->line_tab != NULL && info->line_tab[0] != NULL)
	{
		(ft_strcmp(info->line_tab[0], "cd") == 0) ? builtin_cd(info) : 0;
		(ft_strcmp(info->line_tab[0], "echo") == 0) ? bi_echo(info) : 0;
		if (ft_strcmp(info->line_tab[0], "exit") == 0)
		{
			free(info);
			exit(EXIT_SUCCESS);
		}
		(ft_strcmp(info->line_tab[0], "env") == 0) ? opt_env(info) : 0;
		(ft_strcmp(info->line_tab[0], "unsetenv") == 0) ? bi_unsetenv(info) : 0;
		(ft_strcmp(info->line_tab[0], "setenv") == 0) ? bi_setenv(info) : 0;
	}
	return (0);
}
