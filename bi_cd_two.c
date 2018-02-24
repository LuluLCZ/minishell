/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 19:16:04 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/24 19:16:25 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		error_cd(int i, char *tmp)
{
	if (i == 1)
	{
		write(2, "cd: permission denied: ", 23);
		write(2, tmp, ft_strlen(tmp));
		write(2, "\n", 1);
		free(tmp);
	}
	else if (i == 2)
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, tmp, ft_strlen(tmp));
		write(2, "\n", 1);
		free(tmp);
	}
}

void		cd_tild(t_info *info, char *buf)
{
	char		*tmp;

	tmp = get_env(info->env, "HOME");
	if (ft_strcmp(tmp, "NULL") != 0)
	{
		info = get_env_num(info, "OLDPWD", buf);
		chdir(tmp);
		info = get_env_num(info, "PWD", tmp);
		free(tmp);
	}
	else
	{
		free(tmp);
		write(2, "$HOME doesn't exist, add it with setenv.\n", 41);
	}
}

void		pwd_old_ch(DIR *dir, t_info *info, char *tmp, char *buf)
{
	info = get_env_num(info, "PWD", tmp);
	info = get_env_num(info, "OLDPWD", buf);
	chdir(tmp);
	free(tmp);
	closedir(dir);
}

void		cd_score(t_info *info, char *buf, DIR *dir)
{
	char	*tmp;

	tmp = get_env(info->env, "OLDPWD");
	if (ft_strcmp(tmp, "NULL") != 0)
	{
		if (perm(tmp) == 0)
			error_cd(1, tmp);
		else
		{
			dir = opendir(tmp);
			if (dir != NULL)
			{
				pwd_old_ch(dir, info, tmp, buf);
				info->do_ret = 1;
			}
			else
			{
				error_cd(2, tmp);
				info->do_ret = 1;
			}
		}
	}
	else
		write(2, "$OLDPWD doesn't exist, add it with setenv.\n", 43);
}

void		cd_dir_nul(char *buf, t_info *info)
{
	char	*tmpp;
	char	*tmp;

	tmp = (ft_strcmp(buf, "/") == 0) ? ft_strdup("/") : ft_strjoin(buf, "/");
	tmpp = tmp;
	tmp = ft_strjoin(tmp, info->line_tab[1]);
	if (perm(tmp) == 0)
	{
		write(2, "cd: permission denied: ", 23);
		write(2, info->line_tab[1], ft_strlen(info->line_tab[1]));
		write(2, "\n", 1);
		free(tmp);
	}
	else
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, info->line_tab[1], ft_strlen(info->line_tab[1]));
		write(2, "\n", 1);
		free(tmp);
	}
	free(tmpp);
}
