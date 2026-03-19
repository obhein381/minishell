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
	t_command		*cur;
	t_parser_state	state;

	commands = NULL;
	state.prev = NULL;
	cur = NULL;
	state.cur = token_arr;
	commands = parser_pipe(&commands, &cur, token_arr);
	cur = commands;
	while (state.cur != NULL)
	{
		if (state.cur->type == TOKEN_PIPE)
			cur = parser_pipe(&commands, &cur, token_arr);
		else if (state.cur->type == TOKEN_WORD)
			cur = parser_word(&cur, state);
		else
			cur = parser_redir(&cur, &state);
		if (cur == NULL)
			return (free_token_arr(token_arr), NULL);
		state.prev = state.cur;
		state.cur = state.cur->next;
	}
	//validate_pipe_syntax
	return (commands);
}



