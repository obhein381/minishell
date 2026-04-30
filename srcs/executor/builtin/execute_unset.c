/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:09:09 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/30 11:09:10 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_var(t_shell *shell, int target_index)
{
	free(shell->envp[target_index]);
	while(shell->envp[target_index + 1] != NULL)
	{
		shell->envp[target_index] = shell->envp[target_index + 1];
		target_index++;
	}
	shell->envp[target_index] = NULL;
}

int	execute_unset(t_command *command, t_shell *shell)
{
	char	**argv;
	int		i;
	int		envp_index;

	argv = command->argv;
	i = 1;
	while (argv[i] != NULL)
	{
		envp_index = find_envp_index(shell, argv[i]);
		if (envp_index == -1)
		{
			i++;
			continue ;
		}
		remove_var(shell, envp_index);
		i++;
	}
	return (0);
}
