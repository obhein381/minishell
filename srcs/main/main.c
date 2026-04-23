/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:53:42 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/17 10:53:43 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	int		i;
	char	**envp;

	if (shell->commands != NULL)
	{
		free_command_arr(shell->commands);
		shell->commands = NULL;
	}
	envp = shell->envp;
	if (envp != NULL)
	{
		i = 0;
		while (envp[i] != NULL)
		{
			free(envp[i]);
			i++;
		}
		free(envp);
		shell->envp = NULL;
	}
}

static void	handling_exit_error(t_shell *shell, char *command)
{
	write(2, command, ft_strlen(command));
	free_shell(shell);
	exit(1);
}



void	init_shell(t_shell *shell, char **envp)
{
	shell->commands = NULL;
	shell->envp = NULL;
	shell->input = NULL;
	shell->envp = dup_envp(envp);
	shell->exit_status = CMD_SUCCESS;
	if (shell->envp == NULL)
	{
		handling_exit_error(shell, "malloc error\n");
	}
}

int	handle_main_status(int status, t_shell *shell, t_command **commands)
{
	if (status == CMD_MALLOC_ERROR)
		handling_exit_error(shell, "malloc error\n");
	if (status == CMD_ROLLBACK_ERROR)
		handling_exit_error(shell, "rollback error\n");
	if (status == CMD_EOF)
	{
		free_shell(shell);
		exit(0);
	}
	if (status != CMD_SUCCESS)
	{
		if (*commands != NULL)
			free_command_arr(*commands);
		*commands = NULL;
		shell->commands = NULL;
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int			status;
	t_command	*commands;
	t_shell		shell;

	(void)argv;
	(void)argc;
	init_shell(&shell, envp);
	while (1)
	{
		commands = NULL;
		status = build_commands(&commands, &shell);
		if (handle_main_status(status, &shell, &commands))
			continue ;
		shell.commands = commands;
		status = executor(&shell);
		if (handle_main_status(status, &shell, &commands))
			continue ;
		free_command_arr(commands);
		shell.commands = NULL;
	}
	return (0);
}


