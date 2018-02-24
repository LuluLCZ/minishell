/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:37:59 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/24 18:18:52 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			compare(t_info *info, int i, int j)
{
	if (j == 1)
	{
		while (info->line_tab[i] != NULL &&
		(ft_strcmp("env", info->line_tab[i]) == 0 ||
			ft_strcmp("-i", info->line_tab[i]) == 0))
		{
			if ((ft_strcmp("env", info->line_tab[i]) != 0 &&
				ft_strcmp("-i", info->line_tab[i]) != 0))
				break ;
			else
				i++;
		}
	}
	else if (j == 2)
	{
		if (info->line_tab[i])
			while (info->line_tab[i] != NULL &&
				ft_strcmp(info->line_tab[i], "env") == 0)
				i++;
	}
	return (i);
}

t_info		*new_info_line(t_info *info, int i, int j)
{
	char	*tmp;

	while (info->line_tab[i])
	{
		if (i != j)
			tmp = info->line;
		info->line = ft_strjoin(info->line, info->line_tab[i]);
		if (i != j)
			free(tmp);
		if (info->line_tab[i + 1] != NULL)
		{
			tmp = info->line;
			info->line = ft_strjoin(info->line, " ");
			free(tmp);
		}
		if (info->line_tab[i + 1] == NULL)
			break ;
		i++;
	}
	return (info);
}

void		aff_free(t_info *info, int i, char **tmp)
{
	if (i == 1)
	{
		builtin_env_one(info->env);
		free_tab(info->env);
		info->env = copy_tab(info->env, info->new_en);
		free_tab(info->new_en);
	}
	else if (i == 2)
	{
		builtin_env_one(tmp);
		free_tab_o(tmp);
		free_tab(info->env_n);
	}
	return ;
}

t_info		*free_get_exe(t_info *info, int i, int line, char **tmp)
{
	info = new_info_line(info, i, line);
	free_tab(info->line_tab);
	info->line_tab = ft_strsplit(info->line, ' ');
	i = 0;
	free_tab(info->env);
	info->env = copy_tab(info->env, tmp);
	free_tab(tmp);
	if (builtin(info, i) == 1)
	{
		free_tab(info->line_tab);
		if (info->command)
			free(info->command);
		info = get_command(info, info->env);
	}
	else if (info->line_tab[0] && ft_strcmp(info->line_tab[0], "cd") != 0)
	{
		free_tab(info->line_tab);
		if (info->command)
			free(info->command);
		i = exe(info, 4);
	}
	free_tab(info->env);
	info->env = copy_tab(info->env, info->env_n);
	free_tab(info->env_n);
	return (info);
}

void		env_i(t_info *info)
{
	char	**tmp;
	int		line;
	int		i;

	i = 1;
	info->env_n = copy_tab(info->env_n, info->env);
	tmp = alloc_tab(5120);
	while (info->line_tab[i])
	{
		i = compare(info, i, 1);
		line = i;
		info = err_one(info, i, tmp);
		if (info->do_ret == 1)
			return ;
		i = compare(info, i, 1);
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
