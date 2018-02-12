/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:20:42 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/12 15:39:36 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		bi_echo(t_info *info)
{
	int		i;
	int		j;
	int		k;

	i = 1;
	if (info->line_tab[i] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	while (ft_strcmp(info->line_tab[i], "-n") == 0)
		i++;
	k = i;
	while (info->line_tab[i])
	{
		j = 0;
		if (info->line_tab[i][0] == '$')
		{
			if (ft_strcmp(get_env(info->env, info->line_tab[i] + 1), "NULL") == 0);
			else
				ft_putstr(get_env(info->env, info->line_tab[i] + 1));
			i++;
		}
		else
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
		if (info->line_tab[i])
			write(1, " ", 1);
	}
	if (k != 1)
	{
		write(1, "\033[0;4;47m", 9);
		ft_putchar('%');
		ft_putstr("\033[0m");
	}
	write(1, "\n", 1);
}