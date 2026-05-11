/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 11:57:36 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/28 11:57:39 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handling_error(char *command, int err)
{
	perror(command);
	if (err == ENOENT)
		return (CMD_NOT_FOUND);
	else if (err == EACCES)
		return (CMD_PERMISSION);
	else
		return (1);
}

static int	fd_heredoc_child(t_shell *shell, t_token *file_token, int *fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		exit_code;

	if (pipe(pipe_fd) == -1)
        return (handling_error("pipe", errno));
	pid = fork();
	if (pid  < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (handling_error("fork", errno));
	}
	if (pid == 0)
	{
		set_signal_child();
		close(pipe_fd[0]);
		exit_code = read_heredoc_to_pipe(shell, file_token, pipe_fd);
		close(pipe_fd[1]);
		exit(exit_code);
	}
	close(pipe_fd[1]);
	set_signal_parent_wait();
	if (waitpid(pid, &status, 0) < 0)
	{
		close(pipe_fd[0]);
		set_signal_prompt();
		return (handling_error("waitpid", errno));
	}
	set_signal_prompt();
	return (handle_heredoc_status(status, pipe_fd[0], fd));
}

static int	fd_heredoc_parent(t_shell *shell, t_token *file_token, int *fd)
{
	int	pipe_fd[2];
	int	status;

	if (pipe(pipe_fd) == -1)
		return (handling_error("pipe", errno));
	status = read_heredoc_to_pipe(shell, file_token, pipe_fd);
	close(pipe_fd[1]);
	if (status != CMD_SUCCESS)
	{
		close(pipe_fd[0]);
		return (status);
	}
	*fd = pipe_fd[0];
	return (CMD_SUCCESS);
}

int	fd_heredoc(t_shell *shell, t_token *file_token, int *fd)
{
	if (isatty(STDIN_FILENO))
		return (fd_heredoc_child(shell, file_token, fd));
	return (fd_heredoc_parent(shell, file_token, fd));
}
