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
	int			i;

	n = 0;
	head = commands;
	while (head != NULL)
	{
		printf("%d command fd_in == %d \n",n , head->fd_in);
		printf("%d command fd_out == %d \n",n , head->fd_out);
		printf("%d command argv ==================================== \n", n);
		i = 0;
		while (head->argv[i] != NULL)
		{
			printf("   %d argv == %s \n", i, head->argv[i]);
			i++;
		}
		printf("=================================================== \n");
		n++;
		head = head->next;
	}
	return ;
}

