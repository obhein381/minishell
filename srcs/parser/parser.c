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
	return (0);
}

int	parser_word(t_command **commands, t_token *token_arr)
{
	return (0);
}

t_command	*parser_pipe(t_command **commands)
{
	t_command	*new;

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
	t_token		*cur;
	t_command	*commands;

	cur = token_arr;

	while (cur != NULL)
	{
		if (cur->type == TOKEN_PIPE)
		{
		}
		else if (cur->type == TOKEN_WORD)
		{
		}
		else //tpye == TOKEN_REDIR >, >>, <, << 
		{
		}

	}
	return (commands);
}



