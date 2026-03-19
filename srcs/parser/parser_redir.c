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

t_command	*print_error(t_command *commands, int sign)
{
	//rederection
	if (sign == 1)
		write(2, "parser error redirection\n", 26);
	else
		write(2, "There is no such file or directory.\n", 37);
	free_command_arr(commands);
	return (NULL);
}

int	get_redir_fd(t_token *file_token)
{
	int	fd;

	if (file_token->type == TOKEN_REDIR_IN)
		fd = open(file_token->value, O_RDONLY);
	else //TOKEN_REDIR_OUT)
		fd = open(file_token->value, O_WRONLY);
	//TOKEN_APPEND
	// TOKEN_HEREDOC
	return (fd);
}

void apply_redirection(t_command **commands, t_parser_state state, int fd)
{
	if(state.cur->type == TOKEN_REDIR_IN)
		(*commands)->fd_in = fd;
	else //TOKEN_REDIR_OUT)
		(*commands)->fd_out = fd;
	//TOKEN_APPEND
	// TOKEN_HEREDOC
	return ;
}

t_command	*parser_redir(t_command **commands, t_parser_state *state)
{
	int	fd;
	t_token	*file_token;

	file_token = state->cur->next;
	if (file_token == NULL || file_token->type != TOKEN_WORD)
		return (print_error(*commands, 1));
	fd = get_redir_fd(file_token);
	//TOKEN_APPEND
	// TOKEN_HEREDOC
	if (fd < 0)
		return (print_error(*commands, 2));
	apply_redirection(commands, *state, fd);
	state->cur = file_token;
	//redir need 2 toekn
	return (*commands);
}
