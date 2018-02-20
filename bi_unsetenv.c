/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:29:08 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/20 11:27:05 by llacaze          ###   ########.fr       */
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
	if (!(nenv = (char **)malloc(sizeof(char *) * 100000)))
		return (NULL);
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		if (ft_strcmp(str[0], elem) == 0)
			line++;
		else
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