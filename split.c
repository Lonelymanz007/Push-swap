/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-03 17:01:30 by tphuwian          #+#    #+#             */
/*   Updated: 2026-05-03 17:01:30 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	is_space(char c)
{
	return (c == ' ' || c == '\t' || (c >= 9 && c <= 13));
}

int	count_word(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !is_space(str[i]))
			i++;
	}
	return (count);
}

char	*ft_substr(const char *str, int start, int len)
{
	int		i;
	char	*box;

	i = 0;
	if (!str)
		return (NULL);
	box = (char *)malloc(sizeof(char) * (len + 1));
	if (!box)
		return (NULL);
	while (i < len && str[start] != '\0')
	{
		box[i] = str[start];
		i++;
		start++;
	}
	box[i] = '\0';
	return (box);
}

char	**ft_split(char *str)
{
	int		j;
	char	*s;
	char	**box;

	j = 0;
	box = (char **)malloc(sizeof(char *) * (count_word(str) + 1));
	if (!box)
		return (NULL);
	while (*str)
	{
		while (*str && is_space(*str))
			str++;
		if (*str)
		{
			s = str;
			while (*str && !is_space(*str))
				str++;
			box[j] = ft_substr(s, 0, str - s);
			if (!box[j++])
				return (free_split(box, j - 1));
		}
	}
	box[j] = NULL;
	return (box);
}
