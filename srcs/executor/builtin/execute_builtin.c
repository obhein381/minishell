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

static int	handle_error(char *msg, t_command *command, int *saved_fd)
{
	int	status;

	status = roll_back_fd(saved_fd);
	close_fd(command, saved_fd);
	if (status == 0)
		perror(msg);
	if (status == CMD_ROLLBACK_ERROR)
		return (CMD_ROLLBACK_ERROR);
	return (CMD_DUP_ERROR);
}

int	execute_builtin_child(t_command *command, t_shell *shell, int type)
{
	int	status;

	status = call_cmd(command, shell, type);
	if (status != CMD_SUCCESS)
		return (status);
	return (CMD_SUCCESS);
}

int	execute_builtin(t_command *command, t_shell *shell, int type)
{
	int	status;
	int	saved_fd[2];

	saved_fd[0] = -1;
	saved_fd[1] = -1;
	saved_fd[0] = dup(STDIN_FILENO);
	if (saved_fd[0] == -1)
	{
		perror("dup");
		return (CMD_DUP_ERROR);
	}
	saved_fd[1] = dup(STDOUT_FILENO);
	if (saved_fd[1] == -1)
	{
		close_fd(command, saved_fd);
		perror("dup");
		return (CMD_DUP_ERROR);
	}
	if (command->fd_in != -1)
		if (dup2(command->fd_in, STDIN_FILENO) == -1)
			return (handle_error("dup2", command, saved_fd));
	if (command->fd_out != -1)
		if (dup2(command->fd_out, STDOUT_FILENO) == -1)
			return (handle_error("dup2", command, saved_fd));
	status = call_cmd(command, shell, type);
	if (roll_back_fd(saved_fd) == CMD_ROLLBACK_ERROR)
	{
		close_fd(command, saved_fd);
		return (CMD_ROLLBACK_ERROR);
	}
	close_fd(command, saved_fd);
	if (status != CMD_SUCCESS)
		return (status);
	return (CMD_SUCCESS);
}
