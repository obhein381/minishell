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

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
}

void	shift_argv_left(t_command *command)
{
	int	i;

	i = 0;
	while(command->argv[i + 1] != NULL)
	{
		command->argv[i] = command->argv[i + 1];
		i++;
	}
	command->argv[i] = NULL;
}

int	execute_env(t_command *command, t_shell *shell)
{

	if (shell->envp == NULL)
		return (EMPTY_ENVP);
	if (command->argv[1] == NULL)
	{
		print_env(shell->envp);
		return (CMD_SUCCESS);
	}
	shift_argv_left(command);
	return (execute_external(command, shell->envp));
}

