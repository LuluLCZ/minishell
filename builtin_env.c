/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:37:45 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/02 21:03:06 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env_one(t_info *info)
{
	int		i;

	i = -1;
	while (info->env[++i])
	{
		ft_putstr(info->env[i]);
		write(1, "\n", 1);
	}
}

t_info		*env_refresh(t_info *info)
{
	char	**str;
	char	*line;

	while (*env)
	{
		str = ft_strsplit(*env, '=');
		if (ft_strcmp(str[0], elem) == 0)
		{
			line = ft_strdup(str[1]);
			free(str);
			return (line);
		}
		env++;
	}
	return ("NULL");
}