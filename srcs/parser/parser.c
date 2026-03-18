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

int	parser_redir(t_command **commands, t_token *token_arr)
{
	(void)commands;
	(void)token_arr;
	return (0);
}

int	parser_word(t_command **commands, t_token *token_arr)
{
	(void)commands;
	(void)token_arr;
	return (0);
}

t_command	*parser_pipe(t_command **commands, t_parser_state state)
{
	t_command	*new;

	if (state.prev == NULL || state.cur->next == NULL)
	{
		//error
		return (NULL);
	}
	if (state.cur->next->type != TOKEN_WORD || state.prev->type != TOKEN_WORD)
	{
		//error
		return (NULL);
	}
	new = new_command();
	if (new == NULL)
	{
		free_command_arr(*commands);
		return (NULL);
	}
	*commands = add_back_command(commands, new);
	return (*commands);
}

t_command	*parser(t_token	*token_arr)
{
	t_command		*commands;
	t_parser_state	state;

	commands = NULL;
	state.prev = NULL;
	state.cur = token_arr;

	while (state.cur != NULL)
	{
		if (state.cur->type == TOKEN_PIPE)
		{
		}
		else if (state.cur->type == TOKEN_WORD)
		{
		}
		else //tpye == TOKEN_REDIR >, >>, <, << 
		{
		}
		state.prev = state.cur;
		state.cur = state.cur->next;
	}
	return (commands);
}



