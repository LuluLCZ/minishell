/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:18:39 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/24 17:33:35 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

int		ft_check_char(char *str, char c)
{
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == c)
			count++;
	return (count);
}
