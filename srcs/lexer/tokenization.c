/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:06:15 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/17 11:06:16 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	identify_token(char *input)
{
	if (*input == '|')
		return (TOKEN_PIPE);
	if (*input == '>' && *(input + 1) == '>')
		 return (TOKEN_APPEND);
	if (*input == '>')
		return (TOKEN_REDIR_OUT);
	if (*input == '<' && *(input + 1) == '<')
		return (TOKEN_HEREDOC);
	if (*input == '<')
		return (TOKEN_REDIR_IN);
	if (*input ==' ' || *input == '\t')
		return (TOKEN_SPACE);
	return (TOKEN_WORD);
}

static t_token	*add_token_word(t_token **token_arr, char *input, int *i, int type)
{
	int		len;
	t_token	*new;

	len = 0;
	while (input[len] != '\0' && identify_token(&input[len]) == TOKEN_WORD)
	{
		len++;
	}
	new = new_token(input, len, type);
	if (new == NULL)
		return(free_token_arr(*token_arr));
	*token_arr = add_back_token(new, token_arr);
	*i = *i + len;
	return(*token_arr);
}

static t_token	*add_token_op(t_token **token_arr, char *input, int *i, int type)
{
	t_token	*new;
	int		len;

	len = 1;
	if (type == TOKEN_APPEND || type == TOKEN_HEREDOC)
	{
		len = 2;
	}
	new = new_token(input, len, type);
	if (new == NULL)
		return(free_token_arr(*token_arr));
	*token_arr = add_back_token(new, token_arr);
	*i = *i + len;
	return(*token_arr);
}

int	tokenization(char *input, t_token **token_arr)
{
	int		i;
	int		token_type;

	i = 0;
	while (input[i] != '\0')
	{
		token_type = identify_token(&input[i]);
		if (token_type == TOKEN_SPACE)
			i++;
		else if (token_type == TOKEN_WORD)
		{
			add_token_word(token_arr, &input[i], &i, token_type);
			if (*token_arr == NULL)
				return (MALLOC_ERROR);
		}
		else
		{
			add_token_op(token_arr, &input[i], &i, token_type);
			if (*token_arr == NULL)
				return (MALLOC_ERROR);
		}
	}
	if (*token_arr == NULL)
		return (TOKEN_EMPTY);
	return (0);
}


