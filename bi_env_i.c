/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:37:59 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/23 16:50:50 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			compare(t_info *info, int i)
{
	
}

void		env_i(t_info *info)
{
	int			i;
	int			j;
	char		*tmp;

	i = 1;
	info->new_en = copy_tab(info->new_en, info->env);
	free_tab(info->env);
	if (!(info->env = (char **)malloc(sizeof(char *) * 5121)))
		return ;
	while (info->line_tab[i] != NULL && (ft_strcmp("env", info->line_tab[i]) == 0 || ft_strcmp("-i", info->line_tab[i]) == 0))
	{
		if ((ft_strcmp("env", info->line_tab[i]) != 0 && ft_strcmp("-i", info->line_tab[i]) != 0))
			break ;
		else
			i++;
	}
	j = 0;
	while (info->line_tab[i] && ft_check_char(info->line_tab[i], '=') != 0)
	{
		info->env[j] = ft_strdup(info->line_tab[i]);
		j++;
		i++;
	}
	info->env[j] = NULL;
	while (info->line_tab[i] != NULL && (ft_strcmp("env", info->line_tab[i]) == 0 || ft_strcmp("-i", info->line_tab[i]) == 0))
	{
		if ((ft_strcmp("env", info->line_tab[i]) != 0 && ft_strcmp("-i", info->line_tab[i]) != 0))
			break ;
		else
			i++;
	}
	if (info->line_tab[i] == NULL)
	{
		builtin_env_one(info->env);
		free_tab(info->env);
		info->env = copy_tab(info->env, info->new_en);
		free_tab(info->new_en);
		return ;
	}
	j = i;
	ft_strdel(&info->line);
	while (info->line_tab[i])
	{
		if (i != j)
			tmp = info->line;
		info->line = ft_strjoin(info->line, info->line_tab[i]);
		if (i != j)
			ft_strdel(&tmp);
		tmp = info->line;
		info->line = ft_strjoin(info->line, " ");
		free(tmp);
		if (info->line_tab[i] == NULL)
			break ;
		i++;
	}
	free_tab(info->line_tab);
	ft_strdel(&info->command);
	i = exe(info, 5, "NULL", 0);
	free_tab(info->env);
	info->env = copy_tab(info->env, info->new_en);
	free_tab(info->new_en);
	return ;
}