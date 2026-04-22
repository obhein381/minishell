/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:32:08 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/21 15:32:09 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handling_sig_quote(char **word, int *i)
{
	char	*result;
	int		j;

	result = malloc(ft_strlen(*word) - 1);
	if (result == NULL)
		return (CMD_MALLOC_ERROR);
	j = 0;
	while (j < *i)
	{
		result[j] = (*word)[j];
		j++;
	}
	(*i)++;
	while ((*word)[*i] != '\'')
	{
		result[j] = (*word)[*i];
		j++;
		(*i)++;
	}
	(*i)++;
	while ((*word)[*i] != '\0')
	{
		result[j] = (*word)[*i];
		j++;
		(*i)++;
	}
	free(*word);
	*word = result;
	result[j] = '\0';
}

int	handling_quote(t_token *token_arr)
{
	int		i;
	int		state;
	char	*word;

	word = *token_arr->value;
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
			state = handling_sig_quote(&token_arr->value, &i);
	//	if (word[i] == '\"')
	//		state = handling_dou_quote(token_arr, &i);
	//	if (word[i] == '$')
		if (state != CMD_SUCCESS)
			return (state);
		else
			i++;
	}
	return (CMD_SUCCESS);
}

int	expander(t_shell *shell, t_token **token_arr)
{
	int		i;
	int		state;
	t_token	*head;

	head = *token_arr;
	while (head != NULL)
	{
		i = 0;
		if (head->type == TOKEN_WORD)
		{
			state = handling_quote(head);
		}
		head = head->next;
	}
	return (CMD_SUCCESS);
}

