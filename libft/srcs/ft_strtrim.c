/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 22:06:58 by llacaze           #+#    #+#             */
/*   Updated: 2017/12/12 14:08:13 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/libft.h"

static char		*detect_after(char *s2, char const *s, size_t a, size_t i)
{
	size_t		j;

	j = 0;
	while (s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\n' || \
			s[i - 1] == '\0')
		i--;
	if (!(s2 = (char *)malloc(sizeof(char) * ((i - a) + 1))))
		return (NULL);
	while (a < i)
		s2[j++] = s[a++];
	s2[j] = '\0';
	return (s2);
}

char			*ft_strtrim(char const *s)
{
	char		*s2;
	size_t		i;
	size_t		a;
	size_t		j;

	j = 0;
	a = 0;
	i = 0;
	if (s)
	{
		if (!(s2 = (char *)malloc(sizeof(char) * ((i - a) + 1))))
			return (NULL);
		while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i])
			i++;
		if (s[i] == '\0')
		{
			s2[a] = s[i];
			return (s2);
		}
		a = i;
		i = ft_strlen(s);
		s2 = detect_after(s2, s, a, i);
		return (s2);
	}
	return (NULL);
}
