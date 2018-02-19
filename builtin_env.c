/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:37:45 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/19 19:32:58 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		env_line(t_info *info, char *elem)
{
	char	**str;
	int		line;

	line = 0;
	if (info->line_tab[2] == NULL)
	{
		write(2, "env: option requires an argument -- u\n", 38);
		return ;
	}
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		if (ft_strcmp(str[0], elem) != 0)
		{
			ft_putstr(info->env[line]);
			write(1, "\n", 1);
		}
		line++;
	}
}

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

t_info		*get_env_num(t_info *info, char *elem, char *new_elem)
{
	char	**str;
	int		line;
	char	*tmp;

	line = 0;
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		if (ft_strcmp(str[0], elem) == 0)
		{
			ft_strdel(&info->env[line]);
			info->env[line] = ft_strdup(elem);
			tmp = info->env[line];
			info->env[line] = ft_strjoin(elem, "=");
			ft_strdel(&tmp);
			tmp = info->env[line];
			info->env[line] = ft_strjoin(info->env[line], new_elem);
			ft_strdel(&tmp);
			free_tab(str);
			info->repl = 1;
			return (info);
		}
		free_tab(str);
		line++;
	}
	info->repl = 0;
	return (info);
}

char		**new_env(char **env, char *elem, char *new_elem, char *test)
{
	char	**str;
	int		line;
	char	*tmp;

	line = 0;
	while (env[line] != NULL && ft_strcmp(env[line], "NULL") != 0)
	{
		str = ft_strsplit(env[line], '=');
		if (str && str[0] && ft_strcmp(str[0], elem) == 0)
		{
			free(env[line]);
			env[line] = ft_strdup(elem);
			tmp = env[line];
			env[line] = ft_strjoin(elem, "=");
			free(tmp);
			tmp = env[line];
			env[line] = ft_strjoin(env[line], new_elem);
			free(tmp);
			free_tab(str);
			return (env);
		}
		free_tab(str);
		line++;
		if (env[line] == NULL)
			break ;
	}
	env[line] = ft_strdup(test);
	env[line + 1] = NULL;
	return (env);
}

void		env_equal(t_info *info)
{
	char	**elem;
	char	**tmp;
	char	*tmpp;
	int		line;
	int		i;

	i = 1;
	tmp = copy_tab_o(info->env);
	info->env_n = copy_tab(info->env_n, info->env);
	while (info->line_tab[i])
	{
		if (ft_strcmp(info->line_tab[i], "env") == 0)
			i++;
		else if (info->line_tab[i][0] == '=')
		{
			write(2, "env: ", 5);
			write(2, info->line_tab[i] + 1, ft_strlen(info->line_tab[i] + 1));
			write(2, ": No such file or directory\n", 28);
			// free_tab(tmp);
			return ;
		}
		line = i;
		if (info->line_tab[i] == NULL)
		{
			builtin_env_one(tmp);
			free_tab_o(tmp);
			free_tab(info->env_n);
			// free_info(info);
			return ;
		}
		while (info->line_tab[i] && ft_check_char(info->line_tab[i], '=') != 0)
		{
			if (info->line_tab[i] != NULL)
			{
				elem = ft_strsplit(info->line_tab[i], '=');
				tmp = new_env(tmp, elem[0], elem[1], info->line_tab[i]);
				free_tab(elem);
				i++;
			}
			else
				break ;
		}
		if (i != line && info->line_tab[i] == NULL)
		{
			builtin_env_one(tmp);
			free_tab_o(tmp);
			write(1, "s", 1);
			free_tab(info->env_n);
			// free_info(info);
			return ;
		}
		if (ft_check_char(info->line_tab[i], '=') == 0)
		{
			write(1, "SSDSS", 5);
			line = i;
			ft_strdel(&info->line);
			while (info->line_tab[i])
			{
				if (i != line)
					tmpp = info->line;
				info->line = ft_strjoin(info->line, info->line_tab[i]);
				if (i != line)
					free(tmpp);
				if (info->line_tab[i + 1] != NULL)
				{
					tmpp = info->line;
					info->line = ft_strjoin(info->line, " ");
					free(tmpp);
				}
				if (info->line_tab[i + 1] == NULL)
					break ;
				i++;
			}
			printf("\n[[[%s]]]\n", info->line_tab[i]);
			free_tab(info->env);
			info->env = copy_tab(info->env, tmp);
			free_tab(tmp);
			i = -1;
			free_tab(info->line_tab);
			info->line_tab = ft_strsplit(info->line, ' ');
			if (info->line_tab[0] && ft_strcmp(info->line_tab[0], "cd") != 0)
			{
				free_tab(info->line_tab);
				ft_strdel(&info->command);
				i = exe(info, 4, "NULL");
				free_tab(info->env);
				info->env = copy_tab(info->env, info->env_n);
				free_tab(info->env_n);
				return ;
			}
			// 	free_tab(info->line_tab);
			// free_tab(info->env);
			// info->env = copy_tab(info->env, info->env_n);
			// free_tab(info->env_n);
			return ;
		}
	}
	// free_tab(info->env);
	// info->env = copy_tab(info->env, info->env_n);
	// free_tab(info->env_n);
	// free_tab(tmp);
}

void		env_i(t_info *info)
{
	// pid_t		child_pid;
	int			i;
	int			j;
	char		*tmp;

	i = 1;
	info->new_en = copy_tab(info->new_en, info->env);
	free_tab(info->env);
	if (!(info->env = (char **)malloc(sizeof(char *) * 5121)))
		return ;
	while (info->line_tab[i] && ft_strcmp(info->line_tab[i], "-i") == 0)
		i++;
	j = 0;
	while (info->line_tab[i] && ft_check_char(info->line_tab[i], '=') != 0)
	{
		info->env[j] = ft_strdup(info->line_tab[i]);
		j++;
		i++;
	}
	info->env[j] = NULL;
	while (info->line_tab[i] != NULL && (ft_strcmp("env", info->line_tab[i]) == 0 || ft_strcmp("-i", info->line_tab[i]) == 0))
	{
		if ((ft_strcmp("env", info->line_tab[i]) != 0 && ft_strcmp("-i", info->line_tab[i]) != 0))
			break ;
		else
			i++;
	}
	if (info->line_tab[i] == NULL)
	{
		builtin_env_one(info->env);
		free_tab(info->env);
		info->env = copy_tab(info->env, info->new_en);
		free_tab(info->new_en);
		// free_tab(info->new_en);
		return ;
	}
	j = i;
	ft_strdel(&info->line);
	while (info->line_tab[i])
	{
		if (i != j)
			tmp = info->line;
		info->line = ft_strjoin(info->line, info->line_tab[i]);
		if (i != j)
			ft_strdel(&tmp);
		tmp = info->line;
		info->line = ft_strjoin(info->line, " ");
		free(tmp);
		if (info->line_tab[i] == NULL)
			break ;
		i++;
	}
	free_tab(info->line_tab);
	ft_strdel(&info->command);
	i = exe(info, 5, "NULL");
	free_tab(info->env);
	info->env = copy_tab(info->env, info->new_en);
	free_tab(info->new_en);
	return ;
}

void		opt_env(t_info *info)
{
	// info->env_n = copy_tab(info->env_n, info->env);
	if (info->line_tab[1] == NULL)
		builtin_env_one(info->env);
	else if (ft_strcmp(info->line_tab[1], "-u") == 0)
		env_line(info, info->line_tab[2]);
	else if (ft_strcmp(info->line_tab[1], "-i") == 0)
	{
		env_i(info);
		// info->env = NULL;
		// if (info->env[0])
		// 	free_tab(info->env);
		// info->env = info->env_n;
	}
	else
	{
		env_equal(info);
		// free_tab(info->new_en);
	}
	// info->env = copy_tab(info->env, info->env_n);
	// free_tab(info->env);
}
