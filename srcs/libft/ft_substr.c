/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:54:49 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/26 16:36:25 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;
	size_t	s_len;
	size_t	real_len;

	j = 0;
	i = start;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	real_len = s_len - start;
	if (len > real_len)
		len = real_len;
	p = (char *) malloc (sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	while (j < len)
		p[j++] = s[i++];
	p[j] = '\0';
	return (p);
}
