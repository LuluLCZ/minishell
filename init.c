/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:58:55 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/19 11:19:30 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info		*init_info(void)
{
	t_info		*info;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (NULL);
	info->prev = NULL;
	info->command = NULL;
	info->line = NULL;
	info->line_tab = NULL;
	info->next = NULL;
	return (info);
}

t_info		*refresh_info(t_info *info)
{
	t_info		*tmp;

	tmp = info;
	info = info->next;
	if (!(info = (t_info *)malloc(sizeof(t_info) + 5120000)))
		return (NULL);
	info->prev = tmp;
	info->command = NULL;
	info->line_tab = NULL;
	info->line = NULL;
	info->next = NULL;
	return (info);
}

t_info		*go_begin(t_info *info)
{
	t_info		*tmp;

	while (info && info->prev != NULL)
	{
		tmp = info;
		info = info->prev;
		info->next = tmp;
		tmp = NULL;
	}
	return (info);
}

void		free_info(t_info *info)
{
	if (info->command)
		free(info->command);
	if (info->line)
		free(info->line);
	if (info->line_tab[0] != NULL)
		free_tab(info->line_tab);
}