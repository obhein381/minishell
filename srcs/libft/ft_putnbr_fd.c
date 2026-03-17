/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:01:45 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/28 11:35:45 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	int_to_char(int n, int fd)
{
	char	num;

	if (n / 10 != 0)
	{
		int_to_char(n / 10, fd);
		int_to_char(n % 10, fd);
	}
	else
	{
		num = '0' + n;
		write(fd, &num, 1);
		return ;
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = n * -1;
		write(fd, "-", 1);
	}
	int_to_char(n, fd);
	return ;
}
