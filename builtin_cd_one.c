/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:32:19 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/26 13:22:58 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cd_dir_back(char *buf, t_info *info)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = get_env(info->env, "PWD");
	while (tmp[i] != '\0')
	{
		if (j == ft_check_char(tmp, '/'))
			break ;
		if (tmp[i] == '/')
			j++;
		i++;
	}
	tmp[i] = '\0';
	info->line_tab[1] = ft_strjoin(tmp, info->line_tab[1] + 3);
	chdir(info->line_tab[1]);
	info = get_env_num(info, "OLDPWD", info->line_tab[1]);
	getcwd(buf, 512);
	info = get_env_num(info, "PWD", buf);
	free(tmp);
}

void		cd_dir_back_ok(char *buf, t_info *info)
{
	char *tmp;

	tmp = get_env(info->env, "OLDPWD");
	chdir(tmp);
	free(tmp);
	tmp = get_env(info->env, "PWD");
	getcwd(buf, 512);
	info = get_env_num(info, "OLDPWD", tmp);
	info = get_env_num(info, "PWD", buf);
	free(tmp);
}

void		cd_dir_ok(t_info *info, char *buf)
{
	char	*tmpp;
	char	*tmp;

	if (info->line_tab[1][0] != '/')
	{
		tmp = ft_strjoin(buf, "/");
		tmpp = tmp;
		tmp = ft_strjoin(tmp, info->line_tab[1]);
		free(tmpp);
	}
	else
	{
		tmp = ft_strdup(info->line_tab[1]);
		info = get_env_num(info, "PWD", tmp);
	}
	info = get_env_num(info, "OLDPWD", buf);
	chdir(tmp);
	free(tmp);
	getcwd(buf, 512);
	info = get_env_num(info, "PWD", buf);
}

void		builtin_cd(t_info *info)
{
	char	buf[512];
	DIR		*dir;

	getcwd(buf, 512);
	dir = opendir(info->line_tab[1]);
	if (info->line_tab[1] == NULL || (ft_strcmp(info->line_tab[1], "~")) == 0)
		cd_tild(info, buf);
	else if (ft_strcmp(info->line_tab[1], "-") == 0)
	{
		cd_score(info, buf, dir);
		if (info->do_ret == 1)
			return ;
	}
	else if (dir == NULL)
		cd_dir_nul(buf, info);
	else
	{
		if (dir == NULL && info->line_tab[1][0] == '.' &&
			info->line_tab[1][1] == '.')
			(info->line_tab[1][2] == '/') ? cd_dir_back(buf, info) :
				cd_dir_back_ok(buf, info);
		else
			cd_dir_ok(info, buf);
	}
	dir == NULL ? 0 : closedir(dir);
}
