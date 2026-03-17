/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:10:57 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/26 10:32:53 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dlen;
	size_t	slen;

	j = 0;
	dlen = 0;
	slen = ft_strlen(src);
	if (size == 0)
		return (slen);
	while (dlen < size && dest[dlen] != '\0')
		dlen++;
	if (dlen == size)
		return (size + slen);
	i = dlen;
	while (src[j] && i + 1 < size)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dlen + slen);
}
/*int main (void)
{
	char test1[] = "2a";
	char test2[] = "2";
	size_t size = 4;

	printf("%zu %zu", ft_strlen(test1), ft_strlen(test2));

	printf("%zu\n", ft_strlcat(test1, test2, size));
}*/
