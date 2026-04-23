/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_sig_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:02:17 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/22 12:02:18 by jisulim          ###   ########.fr       */
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

int	handling_sig_quote(char **word, int *i)
{
	remove_quote(word, *i);
	while ((*word)[*i] != '\0' && (*word)[*i] != '\'')
	{
		(*i)++;
	}
	if ((*word)[*i] == '\'')
		remove_quote(word, *i);
	return (CMD_SUCCESS);
}

