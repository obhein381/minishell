/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:21:35 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/07 10:21:41 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handling_error(char *command)
{
	perror(command);
	return (1);
}

static	void	execute_redir(t_command *command, int *fd, int *prev_read)
{
	if (*prev_read != -1)
		dup2(*prev_read, STDIN_FILENO);
	if (command->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (command->fd_in != -1)
		dup2(command->fd_in, STDIN_FILENO);
	if (command->fd_out != -1)
		dup2(command->fd_out, STDOUT_FILENO);
	if (*prev_read != -1)
		close(*prev_read);
	if (command->next != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (command->fd_in != -1)
		close(command->fd_in);
	if (command->fd_out != -1)
		close(command->fd_out);
}

static int	execute_child_cmd(t_command *command, t_shell *shell)
{
	int	builtin_type;
	int	status;

	builtin_type = get_builtin_type(command);
	if (builtin_type == UNKNOWN_COMMAND)
		status = execute_external_child(shell, command);
	else
		status = execute_builtin(shell, builtin_type);
	return (status);
}

int	execute_multi_cmd(t_shell *shell)
{
	t_command	*head;
	int			fd[2];
	int			prev_read;

	prev_read = -1;
	head = shell->commands;
	while (head != NULL)
	{
		if (head->next != NULL)
			if (pipe(fd) < 0)
				return (handling_error("pipe"));
		head->pid = fork();
		if (head->pid < 0)
			return (handling_error("fork"));
		if (head->pid == 0)
		{
			execute_redir(head, fd, &prev_read);
			exit(execute_child_cmd(head, shell));
		}
		if (prev_read != -1)
			close(prev_read);
		if (head->next != NULL)
		{
			close(fd[1]);
			prev_read = fd[0];
		}
		else
			prev_read = -1;
		head = head->next;
	}
	return (wait_all_child(shell->commands));
}
