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

int	get_redir_fd(t_shell *shell, t_token *file_token, int type, int *fd)
{
	int	status;

	status = CMD_SUCCESS;
	if (type == TOKEN_REDIR_IN)
		*fd = open(file_token->value, O_RDONLY);
	else if (type == TOKEN_REDIR_OUT)
		*fd = open(file_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == TOKEN_APPEND)
		*fd = open(file_token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		status = fd_heredoc(shell, file_token, fd);
	if (status != CMD_SUCCESS)
		return (status);
	if (*fd < 0)
		return (perror(file_token->value), -1);
	return (CMD_SUCCESS);
}

void apply_redirection(t_command **commands, int type, int fd)
{
	if (type == TOKEN_REDIR_IN || type == TOKEN_HEREDOC)
	{
		if ((*commands)->fd_in != -1)
			close((*commands)->fd_in);
		(*commands)->fd_in = fd;
	}
	else
	{
		if ((*commands)->fd_out != -1)
			close((*commands)->fd_out);
		(*commands)->fd_out = fd;
	}
	return ;
}

int	parser_redir(t_shell *shell, t_command **commands, t_parser_state *state)
{
	int	fd;
	int	status;
	t_token	*file_token;

	file_token = state->cur->next;
	if (file_token == NULL || file_token->type != TOKEN_WORD)
		return (REDIR_ERROR);
	status = get_redir_fd(shell, file_token, state->cur->type, &fd);
	if (status != CMD_SUCCESS)
	{
		shell->exit_status = status;
		return (status);
	}
	apply_redirection(commands, state->cur->type, fd);
	state->cur = file_token;
	return (CMD_SUCCESS);
}
