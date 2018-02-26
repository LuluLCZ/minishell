/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 18:30:10 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/26 13:23:49 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char		**new_tab(int i, t_info *info, char **tmp)
{
	char **elem;

	elem = ft_strsplit(info->line_tab[i], '=');
	tmp = new_env(tmp, elem[0], elem[1], info->line_tab[i]);
	free_tab(elem);
	return (tmp);
}

t_info		*check_i(t_info *info, char **tmp, int i, int line)
{
	i = compare(info, i, 1);
	if (i != line && info->line_tab[i] == NULL)
	{
		info->do_ret = 1;
		aff_free(info, 2, tmp);
		return (info);
	}
	else if (ft_check_char(info->line_tab[i], '=') == 0)
	{
		info->do_ret = 1;
		line = i;
		ft_strdel(&info->line);
		info = free_get_exe(info, i, line, tmp);
		return (info);
	}
	info->do_ret = 0;
	return (info);
}

t_info		*err_one(t_info *info, int i, char **tmp)
{
	if (info->line_tab[i] == NULL ||
		(info->line_tab[i] && info->line_tab[i][0] == '='))
	{
		info->line_tab[i] == NULL ? aff_free(info, 2, tmp)
			: usage_setenv(i, info, 2, tmp);
		info->do_ret = 1;
		return (info);
	}
	info->do_ret = 0;
	return (info);
}

char		*util_get(char *tmp, char **tab, int i)
{
	free(tmp);
	tmp = ft_strdup(tab[i]);
	free_tab(tab);
	tab = NULL;
	return (tmp);
}
