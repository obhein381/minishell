/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_opt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 17:02:59 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/30 17:03:00 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	roll_back_fd(int *saved_fd)
{ 
	if (saved_fd[0] != -1)
	{
		if (dup2(saved_fd[0], STDIN_FILENO) == -1)
			return (CMD_ROLLBACK_ERROR);
	}
	if (saved_fd[1] != -1)
	{
		if (dup2(saved_fd[1], STDOUT_FILENO) == -1)
			return (CMD_ROLLBACK_ERROR);
	}
	return (0);
}

void	close_fd(t_command *command, int *saved_fd)
{
	if (saved_fd[0] != -1)
		close(saved_fd[0]);
	if (saved_fd[1] != -1)
		close(saved_fd[1]);
	if (command->fd_in != -1)
	{
		close(command->fd_in);
		command->fd_in = -1;
	}
	if (command->fd_out != -1)
	{
		close(command->fd_out);
		command->fd_out = -1;
	}
}

int	call_cmd(t_command *command, t_shell *shell,  int type)
{
	int	status;

	status = CMD_UNKNOWN_ERR;
	if (type == COMMAND_ECHO)
		status = execute_echo(command);
	if (type == COMMAND_ENV)
		status = execute_env(command, shell);
	if (type == COMMAND_EXPORT)
		status = execute_export(command, shell);
	if (type == COMMAND_CD)
		status = execute_cd(command, shell);
	if (type == COMMAND_UNSET)
		status = execute_unset(command, shell);
	if (type == COMMAND_PWD)
		status = execute_pwd();
	if (type == COMMAND_EXIT)
		status = execute_exit(command, shell);
	return (status);
}