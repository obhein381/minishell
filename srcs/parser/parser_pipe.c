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

t_command	*parser_pipe(t_command **commands, t_command **cur, t_token	*token_arr)
{
	t_command	*new;

	new = new_command();
	if (new == NULL)
	{
		//malloc error
		write(2, "malloc error\n", 13);
		free_command_arr(*commands);
		free_token_arr(token_arr);
		exit(1);
	}
	*commands = add_back_command(commands, new);
	(*cur) = new;
	return (*commands);
}
