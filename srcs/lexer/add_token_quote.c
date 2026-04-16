/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:36:21 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/16 13:36:22 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_word_len(t_shell *shell, int *i, int *off_set)
{
	int		word_len;
	int		j;
	int		sig_sign;
	int		dou_sign;
	char	*input;

	input = shell->input;
	sig_sign = 0;
	dou_sign = 0;
	j = 0;
	word_len = 0;
	while (input[*i + j] != '\0')
	{
		if (dou_sign == 0 && sig_sign == 0 && input[*i + j] == '\'')
			sig_sign = 1;
		else if (dou_sign == 0 && sig_sign == 1 && input[*i + j] == '\'')
			sig_sign = 0;
		else if (sig_sign == 0 && dou_sign == 0 && input[*i + j] == '\"')
			dou_sign = 1;
		else if (sig_sign == 0 && dou_sign == 1 && input[*i + j] == '\"')
			dou_sign = 0;
		else
		{
			if (dou_sign != 1 && sig_sign != 1 && identify_token(&input[*i + j]) != TOKEN_WORD)
				break;
			word_len++;
		}
		j++;
	}
	if (dou_sign == 1 || sig_sign == 1)
		return (-1);
	*off_set = j;
	return (word_len);
}

int	make_shell_word(t_shell *shell, char **result, int *i)
{
	int		len;
	int		off_set;

	*result = NULL;
	len = shell_word_len(shell, i, &off_set);
	if (len == -1)
		return (CMD_QUOTE_ERROR);
	*result = malloc(sizeof(char) * (len + 1));
	if (*result == NULL)
		return (CMD_MALLOC_ERROR);
	return (CMD_SUCCESS);
}
