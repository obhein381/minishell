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
		if (head->argv != NULL)
		{
			i = 0;
			while (head->argv[i] != NULL)
			{
				free(head->argv[i]);
				i++;
			}
			free(head->argv);
		}
		free(head);
		head = next;
	}
	return (NULL);
}

void	set_argv(t_command *new, int token_count)
{
	int	i;

	i = 0;
	while (i <= token_count)
	{
		new->argv[i] = NULL;
		i++;
	}
	return ;
}

t_command	*new_command(int token_count)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (new == NULL)
		return (NULL);
	new->argv = malloc(sizeof(char *) * (token_count + 1));
	if (new->argv == NULL)
	{
		free (new);
		return (NULL);
	}
	set_argv(new, token_count);
	new->fd_in = -1;
	new->fd_out = -1;
	new->count = 0;
	new->next = NULL;
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
