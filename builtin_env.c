/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:37:45 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/26 13:41:35 by llacaze          ###   ########.fr       */
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

t_info		*get_env_num(t_info *info, char *elem, char *new_elem)
{
	char	**str;
	int		line;

	line = 0;
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		if (ft_strcmp(str[0], elem) == 0)
		{
			info->env[line] = new_line(info->env[line], elem, new_elem);
			free_tab(str);
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
	while (env[line] != NULL && ft_strcmp(env[line], "NULL") != 0)
	{
		str = ft_strsplit(env[line], '=');
		if (str && str[0] && ft_strcmp(str[0], elem) == 0)
		{
			env[line] = new_line(env[line], elem, new_elem);
			free_tab(str);
			return (env);
		}
		free_tab(str);
		line++;
		if (env[line] == NULL)
			break ;
	}
	env[line] = ft_strdup(test);
	env[line + 1] = NULL;
	return (env);
}

void		env_equal(t_info *info)
{
	char	**tmp;
	int		line;
	int		i;

	i = 1;
	tmp = copy_tab_o(info->env);
	info->env_n = copy_tab(info->env_n, info->env);
	while (info->line_tab[i])
	{
		i = compare(info, i, 2);
		line = i;
		info = err_one(info, i, tmp);
		if (info->do_ret == 1)
			return ;
		i = compare(info, i, 2);
		while (info->line_tab[i] && ft_check_char(info->line_tab[i], '=') != 0)
		{
			if (info->line_tab[i] != NULL)
				tmp = new_tab(i, info, tmp);
			i++;
		}
		info = check_i(info, tmp, i, line);
		if (info->do_ret == 1)
			return ;
	}
}

void		opt_env(t_info *info)
{
	if (info->line_tab[1] == NULL)
	{
		builtin_env_one(info->env);
		return ;
	}
	else if (ft_strcmp(info->line_tab[1], "-u") == 0)
		env_line(info, info->line_tab[2]);
	else if (ft_strcmp(info->line_tab[1], "-i") == 0)
		env_i(info);
	else
		env_equal(info);
}
