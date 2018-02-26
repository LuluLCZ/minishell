/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:26:27 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/26 13:29:52 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		execve_error(t_info *info)
{
	if (info->line_tab[0] != NULL &&
		execve(info->command, info->line_tab, info->env) == -1 &&
		execve(info->line_tab[0], info->line_tab, info->env) == -1)
	{
		write(2, "minishell: command not found: ", 31);
		write(2, info->line_tab[0], ft_strlen(info->line_tab[0]));
		write(2, "\n", 1);
		exit(1);
	}
}

void		exec_cmd(t_info *info)
{
	int		i;
	char	*tmp;
	char	buf[4096];

	i = 6;
	tmp = NULL;
	while (42)
	{
		tmp = getcwd(buf, 4096);
		ft_putstr("\033[0;32m[\033[0m\033[0;34m*");
		ft_putstr(tmp);
		ft_putstr("]*\033[0m\xe2\x86\x92\e[31m\xe2\x98\x85\033[0m ");
		signal(SIGINT, sig_hand_emp);
		if (get_next_line(0, &info->line) > 0)
			exe(info, i);
		i++;
	}
}
