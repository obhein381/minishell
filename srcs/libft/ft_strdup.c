/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:55:31 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/26 10:09:54 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*result;
	size_t	i;

	i = 0;
	result = (char *)malloc(1 * (ft_strlen(src) + 1));
	if (result == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*int main(void)
{
	char *test = "apple";
	int i = 0;
	
	

	while(ft_strdup(test)[i] != 0)
	{
		write(1, &ft_strdup(test)[i], 1);
		i++;
	}
	
}*/
