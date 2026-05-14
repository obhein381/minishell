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

int	handling_tilde(t_shell *shell, char **value, int *i)
{
	int		home_index;
	char	*new_value;

	home_index = find_envp_index(shell, "HOME");
	if (home_index == -1 || shell->envp[home_index][4] != '=')
		return (CMD_SUCCESS);
	new_value = ft_strdup(&(shell->envp[home_index][5]));
	if (new_value == NULL)
		return (MALLOC_ERROR);
	free(*value);
	*value = new_value;
	*i = ft_strlen(*value);
	return (CMD_SUCCESS);
}


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
		if (is_valid_var_start(token_arr->value, i) == 1)
		{
			if (is_only_var_token(token_arr->value, i) == 1)
				token_arr->word_split = 1;
			state = handling_cash(shell, &(token_arr->value), &i);
			if (state != CMD_SUCCESS)
				return (state);
			continue ;
		}
		if (token_arr->value[i] == '~'
			&& i == 0
			&& token_arr->value[i + 1] == '\0')
		{
			state = handling_tilde(shell, &(token_arr->value), &i);
			if (state != CMD_SUCCESS)
				return (state);
			continue ;
		}
		i++;
	}
	return (CMD_SUCCESS);
}

int	expander(t_shell *shell, t_token **token_arr)
{
	int		state;
	t_token	*head;

	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
	state = 0;
	head = *token_arr;
	while (head != NULL)
	{
		if (head->type == TOKEN_HEREDOC)
		{
			if (head->next != NULL && head->next->type == TOKEN_WORD)
			{
				head->next->heredoc_quote = has_quote(head->next->value);
				removal_quote_only(head->next);
				head = head->next->next;
				continue ;
			}
		}
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

