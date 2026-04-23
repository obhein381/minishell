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

int	handling_quote(t_shell *shell, t_token *token_arr)
{
	int		i;
	int		state;

	state = CMD_SUCCESS;
	i = 0;
	while (token_arr->value[i] != '\0')
	{
		if (token_arr->value[i] == '\'')
		{
			state = handling_sig_quote(&(token_arr->value), &i);
			if (state != CMD_SUCCESS)
				return (state);
			continue ;
		}
		if (token_arr->value[i] == '\"')
		{
			state = handling_dou_quote(shell, &(token_arr->value), &i);
			if (state != CMD_SUCCESS)
				return (state);
			continue ;
		}
	//		state = handling_dou_quote(token_arr, &i);
	//	if (token_arr->value[i] == '$')
		i++;
	}
	return (CMD_SUCCESS);
}

int	expander(t_shell *shell, t_token **token_arr)
{
	int		state;
	t_token	*head;

	state = 0;
	head = *token_arr;
	(void)shell;
	while (head != NULL)
	{
		if (head->type == TOKEN_WORD)
		{
			state = handling_quote(shell, head);
			if (state != CMD_SUCCESS)
				return (state);
		}
		head = head->next;
	}
	return (CMD_SUCCESS);
}

