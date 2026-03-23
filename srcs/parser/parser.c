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

static int	count_token(t_token *head)
{
	int	count;

	count = 0;
	while (head != NULL)
	{
		count++;
		head = head->next;
	}
	return (count);
}

static void	set_parser_env(t_command **commands, t_command **cur, t_parser_state *state, t_token *token_arr)
{
	*commands = NULL;
	*cur = NULL;
	state->prev = NULL;
	state->cur = token_arr;
	state->token_count = count_token(token_arr);
}

static t_command	*handling_error(int check_error, t_command *commands)
{
	if (check_error == MALLOC_ERROR)
		write(2, "malloc error\n", 13);
	else if (check_error == PIPE_ERROR)
		write(2, "pipe error\n", 11);
	else if (check_error == REDIR_ERROR)
		write(2, "redir error\n", 12);
	free_command_arr(commands);
	return (NULL);
}

static int	parse_token(t_command **commands, t_command **cur, t_parser_state *state)
{
	int	check_error;

	check_error = 0;
	if (state->cur->type == TOKEN_PIPE)
		check_error = parser_pipe(commands, cur, state->token_count);
	else if (state->cur->type == TOKEN_WORD)
		check_error = parser_word(cur, *state);
	else
		check_error = parser_redir(cur, state);
	return (check_error);
}

t_command	*parser(t_token	*token_arr)
{
	t_command		*commands;
	t_command		*cur;
	t_parser_state	state;
	int				check_error;

	if (token_arr == NULL)
		return (NULL);
	set_parser_env(&commands, &cur, &state, token_arr);
	check_error = parser_pipe(&commands, &cur, state.token_count);
	if (check_error != 0)
		return (handling_error(check_error, commands));
	while (state.cur != NULL)
	{
		check_error = parse_token(&commands, &cur, &state);
		if (check_error != 0)
			return (handling_error(check_error, commands));
		state.prev = state.cur;
		state.cur = state.cur->next;
	}
	if (check_pipe_syntax(commands) == PIPE_ERROR)
		return (handling_error(PIPE_ERROR, commands));
	return (commands);
}
