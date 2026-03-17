/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:29:55 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/25 13:03:19 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *) s + len);
	if (len == 0)
		return (NULL);
	while (len != 0)
	{
		if ((unsigned char)s[len] == (unsigned char) c)
		{
			return ((char *)&s[len]);
		}
		else
			len--;
	}
	if ((unsigned char)s[len] == (unsigned char)c)
		return ((char *)&s[len]);
	return (NULL);
}
/*int main (void)
{
	char test[6] = "ehele";

	printf ("%s", strrchr(test, 'e'));
} if c = '\0'  return  s + len because len = 0, return NULL
*/
