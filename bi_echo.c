/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:20:42 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/03 17:58:03 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		bi_echo(t_info *info)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	i = 1;
	while (ft_strcmp(info->line_tab[i], "-n") == 0)
		i++;
	k = i;
	while (info->line_tab[i])
	{
		while (info->line_tab[i][j])
		{
			if (info->line_tab[i][j] == '\\')
				j++;
			if (info->line_tab[i][j] == '\\' && ft_isascii(info->line_tab[i][j + 1]))
			{
				ft_putchar(info->line_tab[i][j]);
				j++;
			}
			if (info->line_tab[i][j] == '"' && info->line_tab[i][j - 1] != '\\')
				j++;
			else
			{
				ft_putchar(info->line_tab[i][j]);
				j++;
			}
		}
		i++;
	}
	if (k != 1)
	{
		write(1, "\033[7;40", 6);
		ft_putchar('%');
	}
	else
		
	k != 1 ? ft_putstr("\033[1;40;7") : ft_putchar('\n');
	k != 1 ? ft_putstr("\n") : 0;
}