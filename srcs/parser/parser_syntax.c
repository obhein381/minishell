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
		if (head->argv[0] == NULL)
		{
			write(2, "pipe error\n", 12);
			return (1);
		}
		head = head->next;
	}
	return (0);
}