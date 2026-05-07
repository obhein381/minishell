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

static int	handle_heredoc_status(int status, int read_fd, int *fd)
{
	int	exit_code;
	int	sig;

	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code != CMD_SUCCESS)
		{
			close(read_fd);
			return (exit_code);
		}
		*fd = read_fd;
		return (CMD_SUCCESS);
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		close(read_fd);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(2, "\n", 1);
		return (128 + sig);
	}
	close(read_fd);
	return (1);
}

int	heredoc_child(t_shell *shell, t_token *file_token, int *pipe_fd)
{
	char	*eof;
	char	*line;
	int		i;

	eof = file_token->value;
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (file_token->heredoc_quote == 0)
		{
			i = 0;
			while (line[i] != '\0')
			{
				if (is_valid_var_start(line, i) == 1)
				{
					handling_cash(shell, &line, &i);
					if (line == NULL)
						return (HEREDOC_MALLOC_ERROR);
				}
				else
					i++;
			}
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	return (CMD_SUCCESS);
}

int	fd_heredoc(t_shell *shell, t_token *file_token, int *fd)
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
		exit_code = heredoc_child(shell, file_token, pipe_fd);
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
