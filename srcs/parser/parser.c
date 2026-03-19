/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:45:30 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/18 10:45:32 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parser(t_token	*token_arr)
{
	t_command		*commands;
	t_parser_state	state;

	commands = NULL;
	state.prev = NULL;
	state.cur = token_arr;
	commands = parser_pipe(&commands);
	while (state.cur != NULL)
	{
		if (state.cur->type == TOKEN_PIPE)
			commands = parser_pipe(&commands);
		else if (state.cur->type == TOKEN_WORD)
			commands = parser_word(&commands, state);
		else
			commands = parser_redir(&commands, &state);
		if (commands == NULL)
			return (free_token_arr(token_arr), NULL);
		state.prev = state.cur;
		state.cur = state.cur->next;
	}
	//validate_pipe_syntax
	return (commands);
}



