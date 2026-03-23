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

t_command	*parser_pipe(t_command **commands, t_command **cur, int token_count)
{
	t_command	*new;

	new = new_command(token_count);
	if (new == NULL)
	{
		write(2, "malloc error\n", 13);
		return (NULL);
	}
	*commands = add_back_command(commands, new);
	(*cur) = new;
	return (new);
}
