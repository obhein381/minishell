/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:52:16 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/31 10:52:17 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_shell *shell)
{
	char	**envp;
	int		i;

	envp = shell->envp;
	if (envp == NULL)
		return (EMPTY_ENVP);
	i = 0;
	while (envp[i] != NULL)
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (CMD_SUCCESS);
}

