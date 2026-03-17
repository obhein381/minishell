/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:14:25 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/25 11:49:07 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dptr;
	const unsigned char	*sptr;

	i = 0;
	dptr = (unsigned char *) dest;
	sptr = (const unsigned char *) src;
	if (n == 0)
		return (dest);
	if (dest == src)
		return (dest);
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		if (sptr < dptr)
			dptr[n - i - 1] = sptr[n - i - 1];
		else
			dptr[i] = sptr[i];
		i++;
	}
	return (dest);
}
/*int main (void)
{
	char src[6] = "";
	char *dest;

	dest = src + 2;

	ft_memmove(dest, src, 6);
	printf("%s", dest);
}*/
