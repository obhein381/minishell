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

static int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0')
		{
			count++;
			while (str[i] != '\0' && str[i] != ' ')
				i++;
		}
	}
	return (count);
}

static int	count_token(t_token *head)
{
	int	count;

	count = 0;
	while (head != NULL)
	{
		if (head->type == TOKEN_WORD && head->word_split == 1)
			count += count_words(head->value);
		else
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

static int	parse_token(t_shell *shell, t_command **commands, t_command **cur, t_parser_state *state)
{
	int	status;

	status = CMD_SUCCESS;
	if (state->cur->type == TOKEN_PIPE)
		status = parser_pipe(commands, cur, state->token_count);
	else if (state->cur->type == TOKEN_WORD)
		status = parser_word(cur, *state);
	else
		status = parser_redir(shell, cur, state);
	return (status);
}

int parser(t_shell *shell, t_token	*token_arr, t_command **commands)
{
	t_command		*cur;
	t_parser_state	state;
	int				check_error;

	if (token_arr == NULL)
		return (TOKEN_EMPTY);
	set_parser_env(commands, &cur, &state, token_arr);
	check_error = parser_pipe(commands, &cur, state.token_count);
	if (check_error != 0)
		return (check_error);
	while (state.cur != NULL)
	{
		check_error = parse_token(shell, commands, &cur, &state);
		if (check_error != CMD_SUCCESS)
			return (check_error);
		state.prev = state.cur;
		state.cur = state.cur->next;
	}
	if (check_pipe_syntax(*commands) == PIPE_ERROR)
		return (PIPE_ERROR);
	return (0);
}
