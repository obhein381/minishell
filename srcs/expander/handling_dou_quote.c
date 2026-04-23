/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dou_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:42:08 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/22 12:42:09 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quote(char **word, int i)
{
	while ((*word)[i + 1] != '\0')
	{
		(*word)[i] = (*word)[i + 1];
		i++;
	}
	(*word)[i] = (*word)[i + 1];
}

int	handling_dou_quote(t_shell *shell, char **word, int *i)
{
	int		state;

	remove_quote(word, *i);
	while ((*word)[*i] != '\0' && (*word)[*i] != '\"')
	{
		if ((*word)[*i] == '$' 
		&& ((*word)[*i + 1] == '?' 
		|| ft_isalpha((*word)[*i + 1]) 
		|| (*word)[*i + 1] == '_'))
		{
			state = handling_cash(shell, word, i);
			if (state != CMD_SUCCESS)
				return (state);
			continue ;
		}
		(*i)++;
	}
	if ((*word)[*i] == '\"')
		remove_quote(word, *i);
	return (CMD_SUCCESS);
}
