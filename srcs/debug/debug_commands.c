/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:32:24 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/19 12:32:27 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_commands(t_command *commands)
{
	t_command	*head;
	int			n;

	n = 0;
	head = commands;
	while (head != NULL)
	{
		printf("n command fd_in == %d \n", head->fd_in);
		printf("n command fd_out == %d \n", head->fd_out);
		n++;
		head = head->next;
	}
	return ;
}

