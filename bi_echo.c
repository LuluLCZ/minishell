/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:20:42 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/13 15:23:27 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			bi_echo_sec(t_info *info, int i, int j)
{
	if (j == 0)
	{
		if (ft_strcmp(get_env(info->env, "HOME"), "NULL") == 0);
			else
				ft_putstr(get_env(info->env, "HOME"));
		i++;
		return (i);
	}
	else if (j == 1)
	{
		if (info->line_tab[i][1] == '\0')
			ft_putchar(info->line_tab[i][0]);
		if (ft_strcmp(get_env(info->env, info->line_tab[i] + 1), "NULL") == 0);
		else
			ft_putstr(get_env(info->env, info->line_tab[i] + 1));
		i++;
		return (i);
	}
	return (i);
}

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
		if (ft_strcmp(info->line_tab[i], "~") == 0)
			i = bi_echo_sec(info, i, 0);
		else if (info->line_tab[i][0] == '$')
			i = bi_echo_sec(info, i, 1);
		else
		{
			while (info->line_tab[i][j])
			{
				if (info->line_tab[i][j] == '\\')
					;
				if (info->line_tab[i][j] == '\\' && ft_isascii(info->line_tab[i][j + 1]))
				{
					ft_putchar(info->line_tab[i][j]);
				}
				if (info->line_tab[i][j] == '"' && info->line_tab[i][j - 1] != '\\');
				else
					ft_putchar(info->line_tab[i][j]);
				j++;
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