/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:13:00 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/23 14:13:01 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_syntax(t_command *head)
{
	if (head != NULL
		&& head->next == NULL
		&& head->argv[0] == NULL
		&& head->fd_in == -1
		&& head->fd_out == -1)
	{
		return (NO_COMMAND);
	}
	while (head != NULL)
	{
		if (head->argv[0] == NULL && head->fd_in == -1 && head->fd_out == -1)
		{
			return (PIPE_ERROR);
		}
		head = head->next;
	}
	return (0);
}

int	check_redir_syntax(t_token *token_arr)
{

	while (token_arr != NULL)
	{
		if (token_arr->type == TOKEN_WORD || token_arr->type == TOKEN_PIPE)
		{
			token_arr = token_arr->next;
			continue ;
		}
		else
		{
			token_arr = token_arr->next;
			if (token_arr == NULL || token_arr->type != TOKEN_WORD)
				return (REDIR_ERROR);
		}
	}
	return (CMD_SUCCESS);

}