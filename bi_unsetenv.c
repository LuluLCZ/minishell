/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:29:08 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/05 17:39:09 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info		*bi_unset(t_info *info, char *elem)
{
	char	**str;
	int		line;
	int		i;

	line = 0;
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		if (ft_strcmp(str[0], elem) == 0)
		{
			i = line;
			while (info->env[i])
			{
				if (info->env[i + 1] != NULL)
					info->env[i] = ft_strdup(info->env[i + 1]);
				i++;
			}
			info->env[i] = NULL;
			return (info);
		}
		line++;
	}
	return (info);
}

void		bi_unsetenv(t_info *info)
{
	int		i;

	i = 0;
	while (info->line_tab[++i])
		info = bi_unset(info, info->line_tab[i]);
}