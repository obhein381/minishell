/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:00:29 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/25 11:40:29 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*sptr;

	sptr = ((const unsigned char *) s);
	i = 0;
	while (i < n)
	{
		if (sptr[i] == (unsigned char)c)
			return ((void *) &sptr[i]);
		i++;
	}
	return (NULL);
}
