/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:13:27 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/18 16:13:29 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_command	*print_error(t_command *commands, int sign)
{
	//rederection
	if (sign == 1)
		write(2, "parser error redirection\n", 26);
	else if (sign == -1)
		write(2, "There is no such file or directory.\n", 37);
	else
		write(2, "pipe failed\n", 14);
	free_command_arr(commands);
	return (NULL);
}

int	fd_heredoc(t_token *file_token)
{
	char	*eof;
	int		pipe_fd[2];
	char	*line;

	eof = file_token->value;
	if (pipe(pipe_fd) == -1)
		return (-2);
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
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free (line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	get_redir_fd(t_token *file_token, int type)
{
	int	fd;

	if (type == TOKEN_REDIR_IN)
		fd = open(file_token->value, O_RDONLY);
	else if (type == TOKEN_REDIR_OUT)
		fd = open(file_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if(type == TOKEN_APPEND)
		fd = open(file_token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = fd_heredoc(file_token);
	return (fd);
}

void apply_redirection(t_command **commands, t_parser_state state, int fd)
{
	if(state.cur->type == TOKEN_REDIR_IN)
	{
		if ((*commands)->fd_in != -1)
			close((*commands)->fd_in);
		(*commands)->fd_in = fd;
	}
	else if(state.cur->type == TOKEN_REDIR_OUT)
	{
		if ((*commands)->fd_out != -1)
			close((*commands)->fd_out);
		(*commands)->fd_out = fd;
	}
	else if(state.cur->type == TOKEN_APPEND)
	{
		if ((*commands)->fd_out != -1)
			close((*commands)->fd_out);
		(*commands)->fd_out = fd;
	}
	else
	{
		if ((*commands)->fd_in != -1)
			close((*commands)->fd_in);
		(*commands)->fd_in = fd;
	}
	return ;
}

t_command	*parser_redir(t_command **commands, t_parser_state *state)
{
	int	fd;
	t_token	*file_token;

	file_token = state->cur->next;
	if (file_token == NULL || file_token->type != TOKEN_WORD)
		return (print_error(*commands, 1));
	fd = get_redir_fd(file_token, state->cur->type);
	if (fd < 0)
		return (print_error(*commands, fd));
	apply_redirection(commands, *state, fd);
	state->cur = file_token;
	return (*commands);
}
