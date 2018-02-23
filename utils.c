/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 18:30:10 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/23 19:07:37 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	i = compare(info, i);
	if (i != line && info->line_tab[i] == NULL)
		aff_free(info, 2, tmp);
	else if (ft_check_char(info->line_tab[i], '=') == 0)
	{
		line = i;
		ft_strdel(&info->line);
		info = free_get_exe(info, i, line, tmp);
	}
	return (info);
}
