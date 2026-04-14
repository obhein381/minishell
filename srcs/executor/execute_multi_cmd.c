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

static int	handling_error(char *command, t_command *commands, t_command *last_cmd)
{
	int	status;

	status = 1;
	perror(command);
	while (commands != last_cmd)
	{
		if (waitpid(commands->pid, &status, 0) == -1)
		{
			if (errno == EINTR)
				continue ;
			perror("waitpid");
		}
		commands = commands->next;
	}
	return (convert_exit_status(status));
}

static void	handling_dup_error(void)
{
	perror("dup2");
	exit(1);
}

static	void	execute_redir(t_command *command, int *fd, int *prev_read)
{
	if (*prev_read != -1)
		if (dup2(*prev_read, STDIN_FILENO) == -1)
			handling_dup_error();
	if (command->next != NULL)
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			handling_dup_error();
	if (command->fd_in != -1)
		if (dup2(command->fd_in, STDIN_FILENO) == -1)
			handling_dup_error();
	if (command->fd_out != -1)
		if (dup2(command->fd_out, STDOUT_FILENO) == -1)
			handling_dup_error();
	if (*prev_read != -1)
		close(*prev_read);
	if (command->next != NULL)
		close_all_fd(fd);
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
		status = execute_builtin(command, shell, builtin_type);
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
			{
				if (prev_read != -1)
					close(prev_read);
				return (handling_error("pipe", shell->commands, head));
			}
		head->pid = fork();
		if (head->pid < 0)
		{
			if (prev_read != -1)
				close(prev_read);
			if (head->next != NULL)
				close_all_fd(fd);
			return (handling_error("fork", shell->commands, head));
		}
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
