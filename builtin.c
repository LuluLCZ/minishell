/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:42:43 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/05 17:47:34 by llacaze          ###   ########.fr       */
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
		write(1, "\ns\n", 3);
		if (str[i] == ' ')
		{
			new_str[j] = '\\';
			j++;
		}
		new_str[j] = str[i];
		i++;
		j++;
	}
	printf("[%s]", new_str);
	new_str[j] = '\0';
	return (new_str);
}

void		builtin_cd(t_info *info)
{
	char	buf[512];
	DIR		*dir;
	char	*tmp;
	// char	*new_tmp;

	getcwd(buf, 512);
	dir = opendir(info->line_tab[1]);
	if (info->line_tab[1] == NULL || (ft_strcmp(info->line_tab[1], "~")) == 0)
	{
		info = get_env_num(info, "OLDPWD", buf);
		chdir(get_env(info->env, "HOME"));
		info= get_env_num(info, "PWD", get_env(info->env, "HOME"));
	}
	else if (ft_strcmp(info->line_tab[1], "/") == 0)
	{
		info = get_env_num(info, "OLDPWD", buf);
		chdir("/");
		info= get_env_num(info, "PWD", "/");
	}
	else if (ft_strcmp(info->line_tab[1], "-") == 0)
	{
		tmp = get_env(info->env, "OLDPWD");
		dir = opendir(tmp);
		if (dir != NULL)
		{
			info = get_env_num(info, "PWD", tmp);
			info = get_env_num(info, "OLDPWD", buf);
			chdir(tmp);
		}
		else
		{
			write(2, "cd: no such file or directory: ", 31);
			write(2, tmp, ft_strlen(tmp));
			write(2, "\n", 1);
		}
	}
	else if (dir == NULL)
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, info->line_tab[1], ft_strlen(info->line_tab[1]));
		write(2, "\n", 1);
	}
	else
	{
		tmp = (ft_strcmp(buf, "/") == 0) ? ft_strdup("/") : ft_strjoin(buf, "/");
		info = get_env_num(info, "OLDPWD", buf);
		chdir(ft_strjoin(tmp, info->line_tab[1]));
		getcwd(buf, 512);
		info = get_env_num(info, "PWD", buf);		
	}
	dir == NULL ? 0 : closedir(dir);
}

int		builtin(t_info *info)
{
	if (info->line_tab != NULL && info->line_tab[0] != NULL)
	{
		if (ft_strcmp(info->line_tab[0], "cd") == 0)
		{
			builtin_cd(info);
			return (1);
		}
		else if (ft_strcmp(info->line_tab[0], "echo") == 0)
		{
			bi_echo(info);
			return (1);
		}
		else if (ft_strcmp(info->line_tab[0], "exit") == 0)
		{
			free(info);
			exit(EXIT_SUCCESS);
			return (1);
		}
		else if (ft_strcmp(info->line_tab[0], "env") == 0)
		{
			opt_env(info);
			return (1);
		}
		else if (ft_strcmp(info->line_tab[0], "unsetenv") == 0)
		{
			bi_unsetenv(info);
			return (1);
		}
		else if (ft_strcmp(info->line_tab[0], "setenv") == 0)
		{
			bi_setenv(info);
			return (1);
		}
	}
	return (0);
}