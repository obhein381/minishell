/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:39:27 by jisulim           #+#    #+#             */
/*   Updated: 2025/11/13 15:33:59 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

char	*get_next_line(int fd)
{
	static char	*backup[1025];
	char		*origin;
	char		*box;
	ssize_t		len;
	ssize_t		result;

	box = NULL;
	if (fd < 0)
		return (NULL);
	while (ft_gnl_strlen(backup[fd], 1) != 1)
	{
		origin = malloc(BUFFER_SIZE + 1);
		if (origin == NULL)
			return (ft_gnl_clear(&backup[fd], NULL));
		len = read(fd, origin, BUFFER_SIZE);
		result = ft_origin(&origin, &backup[fd], len);
		if (result == -1)
			return (NULL);
		if (result == 0)
			break ;
	}
	return (ft_gnl_print(&backup[fd], 0, 0, box));
}
