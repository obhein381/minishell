/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:04:24 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/25 09:56:48 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (i < len && big[i])
	{
		l = 0;
		if (big[i] == little[l])
		{
			while ((i + l < len) && little[l] && big[i + l])
			{
				if (little[l] == big[i + l])
					l++;
				else
					break ;
			}
			if (little[l] == 0)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/*int main(void)
{
	char test1[] = "baav hello 1232123";
	char test2[] = "hello";

	printf("%s", strnstr(test1, test2, sizeof(test1)));


}*/
