/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:42:09 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/26 13:18:11 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		c1 = s1[i];
		c2 = s2[i];
		if ((c1 - c2) != 0)
			return (c1 - c2);
		else
			i++;
	}
	return (0);
}
/*int main(void)
{
	char test1[9] = "hsl";
	char test2[6] = "hello";
	unsigned int n = 2;
	int result = strncmp(test1, test2, n);

	if (ft_strncmp(test1, test2, n) == 0)
	{
		printf("%d\n", ft_strncmp(test1, test2, n));
	}
	else
	{
		printf("%d\n", ft_strncmp(test1, test2, n));
	}

	printf("%d\n", result);


			return 0;
}*/
/* when n = 0 , strncmp function print out 0 */
