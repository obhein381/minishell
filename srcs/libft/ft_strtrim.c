/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:58:28 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/28 11:36:39 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_setmove(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*result;
	char		*zero_p;
	size_t		start;
	size_t		end;
	size_t		len;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_setmove(s1[start], set))
		start++;
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (ft_setmove(s1[end], set))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	zero_p = result;
	while (start <= end)
		*result++ = s1[start++];
	*result = '\0';
	return (zero_p);
}
