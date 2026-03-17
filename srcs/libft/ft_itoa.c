/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:05:01 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/28 11:38:08 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_digit(int n)
{
	int	count;

	count = 1;
	if (n < 0)
		n = -1 * n;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_rev(char **ptr, size_t len)
{
	char	box;
	size_t	i;

	i = 0;
	while (i < len / 2)
	{
		box = (*ptr)[i];
		(*ptr)[i] = (*ptr)[len - 1 - i];
		(*ptr)[len - 1 - i] = box;
		i++;
	}
	return (*ptr);
}

static void	is_neg(size_t *len, int *n, size_t *sign_neg)
{
	*len = *len + 1;
	*n = *n * -1;
	*sign_neg = 1;
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	i;
	size_t	len;
	size_t	sign_neg;

	sign_neg = 0;
	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = count_digit(n);
	if (n < 0)
		is_neg(&len, &n, &sign_neg);
	result = (char *) malloc (sizeof(char) * (len + 1));
	if (result == NULL)
		return (0);
	while (i < len)
	{
		result[i++] = n % 10 + '0';
		n = n / 10;
		if (i == len - 1 && sign_neg == 1)
			result[i++] = '-';
	}
	result[i] = 0;
	return (ft_rev(&result, len));
}
