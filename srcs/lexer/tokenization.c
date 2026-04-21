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

int	identify_token(char *input)
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

int	end_of_word(char *input, int *sig_quote_sign, int *dou_quote_sign)
{
	if (*input == '\'' && *dou_quote_sign == 0)
		*sig_quote_sign = !(*sig_quote_sign);
	else if (*input == '\"' && *sig_quote_sign == 0)
		*dou_quote_sign = !(*dou_quote_sign);
	else if (identify_token(input) != TOKEN_WORD && *dou_quote_sign == 0 && *sig_quote_sign == 0)
		return (1);
	return (0);
}

static int	add_token_word(t_token **token_arr, char *input, int *i, int type)
{
	int		len;
	int		sig_quote_sign;
	int		dou_quote_sign;
	t_token	*new;

	len = 0;
	sig_quote_sign = 0;
	dou_quote_sign = 0;
	while (input[len + *i] != '\0')
	{
		if (end_of_word (&input[len + *i], &sig_quote_sign, &dou_quote_sign) == 1)
			break;
		len++;
	}
	if (sig_quote_sign != 0 || dou_quote_sign != 0)
		return (CMD_QUOTE_ERROR);
	new = new_token(&input[*i], len, type);
	if (new == NULL)
	{
		free_token_arr(*token_arr);
		return(MALLOC_ERROR);
	}
	*token_arr = add_back_token(new, token_arr);
	*i = *i + len;
	if (*token_arr == NULL)
		return (MALLOC_ERROR);
	return(CMD_SUCCESS);
}

static int	add_token_op(t_token **token_arr, char *input, int *i, int type)
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
	{
		free_token_arr(*token_arr);
		return(MALLOC_ERROR);
	}
	*token_arr = add_back_token(new, token_arr);
	if (*token_arr == NULL)
		return (MALLOC_ERROR);
	*i = *i + len;
	return(CMD_SUCCESS);
}

int	tokenization(char *input, t_token **token_arr)
{
	int		i;
	int		token_type;
	int		status;

	i = 0;
	status = CMD_SUCCESS;
	while (input[i] != '\0')
	{
		token_type = identify_token(&input[i]);
		if (token_type == TOKEN_SPACE)
			i++;
		else if (token_type == TOKEN_WORD)
			status = add_token_word(token_arr, input, &i, token_type);
		else
			status = add_token_op(token_arr, &input[i], &i, token_type);
		if (status != CMD_SUCCESS)
			return (status);
	}
	return (status);
}
