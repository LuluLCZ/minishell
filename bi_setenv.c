/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:06:35 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/07 17:09:27 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info		*set_env(t_info *info, char *elem, char *new_elem, int i)
{
	char	**str;
	int		line;

	line = 0;
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		if (ft_strcmp(str[0], elem) == 0)
		{
			if (i != 0)
			{	
				info->env[line] = ft_strdup(elem);
				info->env[line] = ft_strjoin(elem, "=");
				info->env[line] = ft_strjoin(info->env[line], new_elem);
				info->repl = 1;
			}
			return (info);
		}
		line++;
	}
	info->env[line] = ft_strdup(elem);
	info->env[line] = ft_strjoin(info->env[line], "=");
	info->env[line] = ft_strjoin(info->env[line], new_elem);
	info->env[line + 1] = NULL;
	return (info);
}

void		bi_setenv(t_info *info)
{
	int		i;
	int		j;
	
	i = 1;
	j = 0;
	while (info->line_tab[i])
	{
		if (info->line_tab[i + 2] != NULL)
		{
			j = ft_atoi(info->line_tab[i + 2]);
		}
		info = set_env(info, info->line_tab[i], info->line_tab[i +1 ], j);
		i = i + 3;
	}
	builtin_env_one(info);
}