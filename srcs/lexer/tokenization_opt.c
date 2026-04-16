/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_opt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:37:38 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/17 11:37:39 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *input, int len, int type)
{
	int		i;
	t_token	*new;
	char	*value;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	value = malloc(sizeof(char) * (len + 1));
	if (value == NULL)
	{
		free(new);
		return (NULL);
	}
	i = -1;
	while(++i < len)
		value[i] = input[i];
	value[i] = '\0';
	new->value = value;
	new->next = NULL;
	new->type = type;
	return (new); 
}

t_token	*add_back_token(t_token *new_token, t_token **token_arr)
{
	t_token	*token_path;

	if (new_token == NULL)
		return (NULL);
	if (*token_arr == NULL)
	{
		*token_arr = new_token;
		return (*token_arr);
	}
	token_path = *token_arr;
	while (token_path->next != NULL)
	{
		token_path = token_path->next;
	}
	token_path->next = new_token;
	return(*token_arr);
}

void	free_token_arr(t_token *head)
{
	t_token	*next;

	while(head != NULL)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
}

