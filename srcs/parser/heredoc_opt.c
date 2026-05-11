/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:56:29 by jisulim           #+#    #+#             */
/*   Updated: 2026/05/11 11:56:31 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_heredoc_line(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline("heredoc> ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		remove_newline(line);
	}
	return (line);
}

int	handle_heredoc_status(int status, int read_fd, int *fd)
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

int	read_heredoc_to_pipe(t_shell *shell, t_token *file_token, int *pipe_fd)
{
	char	*eof;
	char	*line;
	int		i;

	eof = file_token->value;
	while (1)
	{
		line = read_heredoc_line();
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