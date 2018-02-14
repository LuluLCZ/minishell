/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:37:45 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/14 19:48:34 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		env_line(t_info *info, char *elem)
{
	char	**str;
	int		line;

	line = 0;
	if (info->line_tab[2] == NULL)
	{
		write(2, "env: option requires an argument -- u\n", 38);
		return ;
	}
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		if (ft_strcmp(str[0], elem) != 0)
		{
			ft_putstr(info->env[line]);
			write(1, "\n", 1);
		}
		line++;
	}
}

void		builtin_env_one(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		ft_putstr(env[i]);
		write(1, "\n", 1);
	}
}

t_info		*get_env_num(t_info *info, char *elem, char *new_elem)
{
	char	**str;
	int		line;
	char	*tmp;

	line = 0;
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		if (ft_strcmp(str[0], elem) == 0)
		{
			free(info->env[line]);
			info->env[line] = ft_strdup(elem);
			tmp = info->env[line];
			info->env[line] = ft_strjoin(elem, "=");
			free(tmp);
			tmp = info->env[line];
			info->env[line] = ft_strjoin(info->env[line], new_elem);
			free(tmp);
			// free_tab(str);
			info->repl = 1;
			return (info);
		}
		free_tab(str);
		line++;
	}
	info->repl = 0;
	return (info);
}

char		**new_env(char **env, char *elem, char *new_elem, char *test)
{
	char	**str;
	int		line;

	line = 0;
	while (env[line])
	{
		str = ft_strsplit(env[line], '=');
		if (ft_strcmp(str[0], elem) == 0)
		{
			// tmp = env[line];
			env[line] = ft_strdup(elem);
			// free(tmp);
			// tmp = env[line];
			env[line] = ft_strjoin(elem, "=");
			// free(tmp);
			// tmp = env[line];
			env[line] = ft_strjoin(env[line], new_elem);
			// free(tmp);
			return (env);
		}
		line++;
	}
	env[line] = ft_strdup(test);
	env[line + 1] = NULL;
	return (env);
}

void		env_equal(t_info *info)
{
	char	**elem;
	char	**tmp;
	int		line;
	int		i;

	i = 1;
	line = -1;
	if (!(tmp = (char **)malloc(sizeof(char *) * 51200)))
		return ;
	while(info->env[++line])
	{
		tmp[line] = ft_strdup(info->env[line]);
		if (info->env[line] == NULL)
			break ;
	}
	line = 0;
	while (info->line_tab[i])
	{
		if (ft_strcmp(info->line_tab[i], "env") == 0)
			i++;
		else if (info->line_tab[i][0] == '=')
		{
			write(2, "env: ", 5);
			write(2, info->line_tab[i] + 1, ft_strlen(info->line_tab[i] + 1));
			write(2, ": No such file or directory\n", 28);
			return ;
		}
		else if (ft_check_char(info->line_tab[i], '=') == 0)
		{
			info->line = NULL;
			while (info->line_tab[i])
			{
				info->line = ft_strjoin(info->line, info->line_tab[i]);
				if (info->line_tab[i + 1] != NULL)
					info->line = ft_strjoin(info->line, " ");
				if (info->line_tab[i] == NULL)
					break ;
				i++;
			}
			info->env = NULL;
			info->env = tmp;
			free_tab(info->line_tab);
			info->line_tab = ft_strsplit(info->line, ' ');
			if (ft_strcmp(info->line_tab[0], "cd") != 0)
				i = exe(info, 0);
			// write(2, "env: ", 5);
			// write(2, info->line_tab[i], ft_strlen(info->line_tab[i]));
			// write(2, ": No such file or directory\n", 28);
			return ;
		}
		else
		{
			elem = ft_strsplit(info->line_tab[i], '=');
			tmp = new_env(tmp, elem[0], elem[1], info->line_tab[i]);
			i++;
		}
	}
	i = -1;
	while (tmp[++i])
	{
		ft_putstr(tmp[i]);
		write(1, "\n", 1);
	}
	free(tmp[i]);
}

void		env_i(t_info *info)
{
	// pid_t		child_pid;
	int			i;
	int			j;
	char		*tmp;

	i = 1;
	if  (!(info->new_en = (char **)malloc(sizeof(char *) * 512)))
		return ;
	while (info->line_tab[i] && ft_strcmp(info->line_tab[i], "-i") == 0)
		i++;
	j = 0;
	while (info->line_tab[i] && ft_check_char(info->line_tab[i], '=') != 0)
	{
		info->new_en[j] = ft_strdup(info->line_tab[i]);
		j++;
		i++;
	}
	while (info->line_tab[i] != NULL && (ft_strcmp("env", info->line_tab[i]) == 0 || ft_strcmp("-i", info->line_tab[i]) == 0))
	{
		if ((ft_strcmp("env", info->line_tab[i]) != 0 && ft_strcmp("-i", info->line_tab[i]) != 0))
			break ;
		else
			i++;
	}
	if (info->line_tab[i] == NULL)
	{
		builtin_env_one(info->new_en);
		return ;
	}
	j = i;
	info->new_en[j] = NULL;
	info->line = NULL;
	while (info->line_tab[i])
	{
		tmp = info->line;
		info->line = ft_strjoin(info->line, info->line_tab[i]);
		info->line = ft_strjoin(info->line, " ");
		free(tmp);
		if (info->line_tab[i] == NULL)
			break ;
		i++;
	}
	info->env = info->new_en;
	i = exe(info, 1);
	return ;
}

void		opt_env(t_info *info)
{
	info->env_n = info->env;	
	if (info->line_tab[1] == NULL)
		builtin_env_one(info->env);
	else if (ft_strcmp(info->line_tab[1], "-u") == 0)
		env_line(info, info->line_tab[2]);
	else if (ft_strcmp(info->line_tab[1], "-i") == 0)
	{
		info->env_n = info->env;
		info->env = NULL;
		env_i(info);
		free(info->env);
		info->env = info->env_n;
	}
	else
	{
		info->env_n = info->env;
		env_equal(info);
		free(info->env);
		info->env = info->env_n;
	}
	info->env = info->env_n;
}
