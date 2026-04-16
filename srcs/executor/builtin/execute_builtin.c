/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:03:34 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/25 13:03:36 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	call_cmd(t_command *command, t_shell *shell,  int type)
{
	int	status;

	status = CMD_UNKNOWN_ERR;
	if (type == COMMAND_ECHO)
		status = execute_echo(command);
	if (type == COMMAND_ENV)
		status = execute_env(shell);
	if (type == COMMAND_EXPORT)
		status = execute_export(command, shell);
	/*if (type == COMMAND_CD)
	if (type == COMMAND_PWD)
	if (type == COMMAND_EXPORT)
	if (type == COMMAND_UNSET)
	if (type == COMMAND_ENV)
	if (type == COMMAND_EXIT)
	if (type == COMMAND_MIN_N)*/
	return (status);
}

int	roll_back_fd(int *saved_fd, int cmd_in, int cmd_out)
{ 
	if (cmd_in != -1)
	{
		if (dup2(saved_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (CMD_ROLLBACK_ERROR);
		}
	}
	if (cmd_out != -1)
	{
		if (dup2(saved_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (CMD_ROLLBACK_ERROR);
		}
	}
	return (0);
}

static void	close_fd(int *saved_fd, int cmd_in, int cmd_out)
{
	if (saved_fd[0] != -1)
		close(saved_fd[0]);
	if (saved_fd[1] != -1)
		close(saved_fd[1]);
	if (cmd_in != -1)
		close(cmd_in);
	if (cmd_out != -1)
		close(cmd_out);
}

static int	handle_error(char *command, int *saved_fd, int cmd_in, int cmd_out)
{
	int	status;

	status = roll_back_fd(saved_fd, cmd_in, cmd_out);
	close_fd(saved_fd, cmd_in, cmd_out);
	if (status == 0)
		perror(command);
	if (status == CMD_ROLLBACK_ERROR)
		return (CMD_ROLLBACK_ERROR);
	return (CMD_DUP_ERROR);
}

int	execute_builtin(t_command *command, t_shell *shell, int type)
{
	int	status;
	int saved_fd[2];

	saved_fd[0] = -1;
	saved_fd[1] = -1;
	saved_fd[0] = dup(STDIN_FILENO);
	if (saved_fd[0] == -1)
		return (handle_error("dup", saved_fd, -1, -1));
	saved_fd[1] = dup(STDOUT_FILENO);
	if (saved_fd[1] == -1)
		return (handle_error("dup", saved_fd, -1, -1));
	if (command->fd_in != -1)
		if (dup2(command->fd_in, STDIN_FILENO) == -1)
			return (handle_error("dup2", saved_fd, command->fd_in, -1));
	if (command->fd_out != -1)
		if (dup2(command->fd_out, STDOUT_FILENO) == -1)
			return (handle_error("dup2", saved_fd, command->fd_in, command->fd_out));
	status = call_cmd(command, shell, type);
	if (roll_back_fd(saved_fd, command->fd_in, command->fd_out) == CMD_ROLLBACK_ERROR)
	{
		close_fd(saved_fd, command->fd_in, command->fd_out);
		return (CMD_ROLLBACK_ERROR);
	}
	close_fd(saved_fd, command->fd_in, command->fd_out);
	if (status != CMD_SUCCESS)
		return (status);
	return (CMD_SUCCESS);
}
