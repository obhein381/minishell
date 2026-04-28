/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:39:54 by jisulim           #+#    #+#             */
/*   Updated: 2025/11/13 13:38:20 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

ssize_t	ft_gnl_strlen(char *s, int ver)
{
	ssize_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	if (ver == 0)
	{
		while (s[len] != '\0')
			len++;
	}
	else
	{
		while (s[len] != '\0' && s[len] != '\n')
			len++;
		if (s[len] == '\0')
			return (0);
		return (1);
	}
	return (len);
}

char	*ft_gnl_clear(char **backup, char **sub)
{
	if (backup != NULL && *backup != NULL)
	{
		free(*backup);
		*backup = NULL;
	}
	if (sub != NULL && *sub != NULL)
	{
		free(*sub);
		*sub = NULL;
	}
	return (NULL);
}

char	*ft_gnl_strjoin(char **s, char *s1, char *s2)
{
	ssize_t	len;
	char	*p;
	char	*first;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (ft_gnl_strlen(s1, 0) > SSIZE_MAX - ft_gnl_strlen(s2, 0))
		return (NULL);
	len = ft_gnl_strlen(s1, 0) + ft_gnl_strlen(s2, 0);
	p = malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (ft_gnl_clear(s, NULL));
	first = p;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = 0;
	ft_gnl_clear(s, NULL);
	*s = first;
	return (*s);
}

char	*ft_gnl_print(char **backup, ssize_t i, ssize_t len, char *result)
{
	if (backup == NULL || *backup == NULL)
		return (NULL);
	while ((*backup)[i] != '\0' && (*backup)[i] != '\n')
		i++;
	if ((*backup)[i] == '\0')
		len = i;
	else if ((*backup)[i] == '\n')
		len = i + 1;
	result = malloc(len + 1);
	if (result == NULL)
		return (ft_gnl_clear(backup, NULL));
	i = -1;
	while (++i < len)
		result[i] = (*backup)[i];
	result[i] = '\0';
	if ((*backup)[len] == '\0')
		ft_gnl_clear(backup, NULL);
	else
	{
		*backup = ft_gnl_strjoin(backup, &(*backup)[len], "");
		if (*backup == NULL)
			return (ft_gnl_clear(backup, &result));
	}
	return (result);
}

ssize_t	ft_origin(char **origin, char **backup, ssize_t len)
{
	if (len < 0)
	{
		ft_gnl_clear(origin, backup);
		return (-1);
	}
	if (len == 0)
	{
		ft_gnl_clear(origin, NULL);
		return (0);
	}
	(*origin)[len] = '\0';
	if (*backup == NULL)
		*backup = ft_gnl_strjoin(backup, *origin, "");
	else
		*backup = ft_gnl_strjoin(backup, *backup, *origin);
	if (*backup == NULL)
	{
		ft_gnl_clear(backup, origin);
		return (-1);
	}
	ft_gnl_clear(NULL, origin);
	return (1);
}
