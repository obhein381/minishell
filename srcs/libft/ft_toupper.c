/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:58:02 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/26 12:58:41 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c - 32);
	else
		return (c);
}

/*int	main(void)
{
	char test[6] = "hEllo";
	int i=0;
	ft_strupcase(test);
	while(i<5)
	{
		write(1, &test[i], 1);
		i++;
	}
}*/
