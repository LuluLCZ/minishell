/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:43:48 by llacaze           #+#    #+#             */
/*   Updated: 2018/02/23 14:55:39 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

void	free_tab_o(char **str)
{
	int		i;

	i = -1;
	while (str[++i + 1] != NULL)
	{
		printf("\n(%s)\n", str[i]);
		free(str[i]);
	}
	printf("\n[%s]\n", str[i]);
	free(str[i]);
	free(str);
}

void	free_tab(char **str)
{
	int		i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

char	**copy_tab_o(char **tmp)
{
	int		i;
	char	**env;
	
	i = -1;
	if (!(env = (char **)malloc(sizeof(char *) * 20480)))
		return (NULL);
	while (tmp[++i])
		env[i] = ft_strdup(tmp[i]);
	env[i] = NULL;
	return (env);
}

char	**copy_tab(char **env, char **oenv)
{
	int	i;

	i = -1;
	
	// if (env[0] && env[1])
	// 	free_tab(env);
	// else if (env[0] && !env[1])
	// 	free(env);
	if (!(env = (char **)malloc(sizeof(char *) * 2048)))
		return (NULL);
	while (oenv[++i])
		env[i] = ft_strdup(oenv[i]);
	env[i] = NULL;
	return (env);
}