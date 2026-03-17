/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:59:06 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/21 10:54:03 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
		{
			return ((char *)(s));
		}
		else
			s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}
/*int main(void)
{
	char test[6] = "hello";

	printf("%s", strchr(test,'e'));
}*/
