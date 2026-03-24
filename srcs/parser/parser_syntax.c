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

int			check_pipe_syntax(t_command *head)
{
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