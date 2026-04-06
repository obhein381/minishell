/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export_opt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:51:00 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/06 12:51:02 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_key_index(char *argv)
{
	int	i;

	i = 0;
	while(argv[i] != '\0')
	{
		if (argv[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	check_key(char *argv, int n)
{
	int	i;

	if (ft_isalpha(argv[0]) != 1 && argv[0] != '_')
		return (1);
	i = 1;
	while (argv[i] != '\0' && i < n)
	{
		if (ft_isalnum(argv[i]) != 1 && argv[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	find_key_envp(char **envp, char *key, int key_index)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, key_index) == 0 && envp[i][key_index] == '=')
			return (i);
		i++;
	}
	return (-1);
}
