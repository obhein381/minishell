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

t_command	*parser_redir(t_command **commands, t_parser_state state)
{
	if (state.cur->next == NULL)
	{
		//parser error
		return (free_command_arr(*commands));
	}
	if (state.cur->next->type != TOKEN_WORD)
	{
		//parser error
		return (free_command_arr(*commands));
	}
	return (*commands);
}
