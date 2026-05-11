/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:13:47 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/18 16:13:49 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_word(t_command **commands, char *word)
{
	(*commands)->argv[(*commands)->count] = ft_strdup(word);
	if ((*commands)->argv[(*commands)->count] == NULL)
		return (MALLOC_ERROR);
	(*commands)->count++;
	(*commands)->argv[(*commands)->count] = NULL;
	return (CMD_SUCCESS);
}

static int	add_split_words(t_command **commands, char *value)
{
	char	**words;
	int		i;

	words = ft_split(value, ' ');
	if (words == NULL)
		return (MALLOC_ERROR);
	i = 0;
	while (words[i] != NULL)
	{
		if (add_word(commands, words[i]) != CMD_SUCCESS)
		{
			free_dirs(words);
			return (MALLOC_ERROR);
		}
		i++;
	}
	free_dirs(words);
	return (CMD_SUCCESS);
}

int	parser_word(t_command **commands, t_parser_state state)
{
	if (state.cur->word_split == 1)
		return (add_split_words(commands, state.cur->value));
	return (add_word(commands, state.cur->value));
}
