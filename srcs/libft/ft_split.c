/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:49:56 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/28 11:36:27 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcount(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c && *s != 0)
		{
			if (*(s + 1) == c || *(s + 1) == 0)
				count++;
		}
		s++;
	}
	return (count);
}

static size_t	wordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static void	ft_input(char **result, size_t i, char c, const char **p)
{
	size_t	j;
	size_t	box;

	box = wordlen(*p, c);
	j = 0;
	while (j < box)
	{
		result[i][j] = **p;
		j++;
		(*p)++;
	}
	result[i][j] = 0;
}

static char	**ft_allfree(char **result, size_t i)
{
	while (i > 0)
	{
		free(result[--i]);
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	words;

	i = 0;
	if (!s)
		return (NULL);
	words = wordcount(s, c);
	result = malloc(sizeof(*result) * ((words + 1)));
	if (result == NULL)
		return (NULL);
	while (i < words && *s)
	{
		if (*s != c)
		{
			result[i] = malloc(wordlen(s, c) + 1);
			if (result[i] == NULL)
				return (ft_allfree(result, i));
			ft_input(result, i++, c, &s);
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
