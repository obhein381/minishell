/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:31:51 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/21 11:43:37 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
/*int main(void)
{
	char test[6] = "HeLLO";
	int i = 0;
	ft_strlowcase(test);
	while(test[i] != 0)
	{
		write(1, &test[i], 1);
		i++;
	}
}*/
