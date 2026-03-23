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

t_command	*parser_word(t_command **commands, t_parser_state state)
{

	(*commands)->argv[(*commands)->count] = ft_strdup(state.cur->value);
	if ((*commands)->argv[(*commands)->count] == NULL)
		return (NULL);
	(*commands)->count++;
	(*commands)->argv[(*commands)->count] = NULL;
	return (*commands);
}
