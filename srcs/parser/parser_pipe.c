/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:14:08 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/18 16:14:09 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parser_pipe(t_command **commands, t_parser_state state)
{
	t_command	*new;

	if (state.prev == NULL || state.cur->next == NULL)
	{
		//parser error
		return (free_command_arr(*commands));
	}
	if (state.cur->next->type != TOKEN_WORD || state.prev->type != TOKEN_WORD)
	{
		//parser error
		return (free_command_arr(*commands));
	}
	new = new_command();
	if (new == NULL)
	{
		//malloc error
		return (free_command_arr(*commands));
	}
	*commands = add_back_command(commands, new);
	return (*commands);
}
