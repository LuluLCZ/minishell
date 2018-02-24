/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:29:08 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/24 18:22:39 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info		*bi_unset(t_info *info, char *elem)
{
	char	**str;
	char	**nenv;
	int		line;
	int		i;

	line = 0;
	i = 0;
	nenv = alloc_tab(2048);
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		(ft_strcmp(str[0], elem) == 0) ? line++ : 0;
		if (ft_strcmp(str[0], elem) != 0)
		{
			nenv[i] = ft_strdup(info->env[line]);
			i++;
			line++;
			nenv[i] = NULL;
		}
		free_tab(str);
	}
	free_tab(info->env);
	info->env = copy_tab(info->env, nenv);
	free_tab_o(nenv);
	return (info);
}

void		bi_unsetenv(t_info *info)
{
	int		i;

	i = 0;
	while (info->line_tab[++i])
		info = bi_unset(info, info->line_tab[i]);
}
