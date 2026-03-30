/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:00:50 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/30 14:00:51 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	envp_len(char **envp)
{
	int	len;

	len = 0;
	while (envp[len] != NULL)
		len++;
	return (len);
}

static void	free_envp(char **new_envp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(new_envp[i]);
		i++;
	}
	free(new_envp);
}

char	**dup_empty_envp(void)
{
	char **new_envp;

	new_envp = malloc(sizeof(char *));
	if (new_envp == NULL)
		return (NULL);
	new_envp[0] = NULL;
	return (new_envp);
}

char	**dup_envp(char **envp)
{
	int		len;
	int		i;
	char	**new_envp;

	new_envp = NULL;
	if (envp == NULL)
		return (dup_empty_envp());
	len = envp_len(envp);
	new_envp = malloc(sizeof(char *) * (len + 1));
	if (new_envp == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			free_envp(new_envp, i);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

