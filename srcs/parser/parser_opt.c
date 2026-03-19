/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:45:51 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/18 10:46:02 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*free_command_arr(t_command *head)
{
	t_command	*next;
	int			i;

	while(head != NULL)
	{
		next = head->next;
		if (head->commands != NULL)
		{
			i = 0;
			while (head->commands[i] != NULL)
			{
				free(head->commands[i]);
				i++;
			}
			free(head->commands);
		}
		free(head);
		head = next;
	}
	return (NULL);
}

t_command	*new_command(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (new == NULL)
		return (NULL);
	new->fd_in = -1;
	new->fd_out = -1;
	new->next = NULL;
	new->commands = NULL;
	return (new);
}

t_command	*add_back_command(t_command **commands, t_command *new)
{
	t_command	*head;

	if (*commands == NULL)
	{
		*commands = new;
		return (*commands);
	}
	head = *commands;
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = new;
	return (*commands);
}
