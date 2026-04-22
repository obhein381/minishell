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
	result[j] = '\0';
	free(*word);
	*word = result;
	*i = 0;
	return (CMD_SUCCESS);
}

