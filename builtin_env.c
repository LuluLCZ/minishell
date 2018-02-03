/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:37:45 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/03 17:20:23 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_info		*remove_quot(t_info *info)
// {
// 	int		i;
// 	char	*s;
// 	int		j;

// 	i = 0;
// 	j = 1;
// 	s = ft_strnew(ft_strlen(info->line) + ft_check_char(info->line, ' ') + 5000);
// 	s[j - 1] = '"';
// 	while (info->line[i])
// 	{
// 		while (info->line[i] != ' ')
// 		{
// 			if (info->line[i] == '\\')
// 				i++;
// 			s[j] = info->line[i];
// 			j++;
// 			i++;
// 		}
// 		if (info->line[i] == ' ' && info->line[i-1] != ' ')
// 		{
// 			s[j] = '"';
// 			j++;
// 		}
// 		i++;
// 	}
// 	s[j] = '\0';
// 	free(info->line);
// 	info->line = ft_strdup(s);
// 	free(s);
// 	return (info);
// }

// /*
// 	On a : cd "salut lol"
// 	et : cd salut\ lol
// 	doit 
// */

// char	**ft_strsplit_arg(char const *s, char c)
// {
// 	char		**tab;
// 	size_t		i;
// 	size_t		j;
// 	int			start;
// 	int			end;

// 	tab = NULL;
// 	j = 0;
// 	i = 0;
// 	if (s && (tab = (char **)malloc(sizeof(char *) * ft_strlen(s))))
// 	{
// 		while (s[i] != '\0')
// 		{
// 			while (s[i] == c && s[i] != '\0')
// 				i++;
// 			start = i;
// 			while (s[i] != c && s[i] != '\0')
// 				i++;
// 			end = i;
// 			if (end > start)
// 				tab[j++] = ft_strsub(s, start, (end - start));
// 		}
// 		tab[j] = NULL;
// 	}
// 	return (tab);
// }

void		builtin_env_one(t_info *info)
{
	int		i;

	i = -1;
	while (info->env[++i])
	{
		ft_putstr(info->env[i]);
		write(1, "\n", 1);
	}
}

// t_info		*args_quote(t_info *info)
// {
// 	int		i;
// 	char	**tab;
// 	int		j;

// 	j = 0;
// 	i = 0;
// 	tab = info->line_tab;


// 	}
// 	return (info);
// }

t_info		*get_env_num(t_info *info, char *elem, char *new_elem)
{
	char	**str;
	int		line;

	line = 0;
	while (info->env[line])
	{
		str = ft_strsplit(info->env[line], '=');
		if (ft_strcmp(str[0], elem) == 0)
		{
			info->env[line] = ft_strdup(elem);
			info->env[line] = ft_strjoin(elem, "=");
			info->env[line] = ft_strjoin(info->env[line], new_elem);
			return (info);
		}
		line++;
	}
	return (info);
}

// t_info		*env_refresh(t_info *info)
// {
// 	char	**str;
// 	char	*line;

// 	while (*env)
// 	{
// 		str = ft_strsplit(*env, '=');
// 		if (ft_strcmp(str[0], elem) == 0)
// 		{
// 			line = ft_strdup(str[1]);
// 			free(str);
// 			return (line);
// 		}
// 		env++;
// 	}
// 	return ("NULL");
// }