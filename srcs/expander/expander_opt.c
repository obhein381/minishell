/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:27:19 by jisulim           #+#    #+#             */
/*   Updated: 2026/05/14 12:27:23 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_var_token(char *str, int i)
{
	int	j;

	if (i != 0)
		return (0);
	if (str[i] != '$')
		return (0);
	if (str[i + 1] == '?')
		return (str[i + 2] == '\0');
	if (ft_isalpha(str[i + 1]) != 1 && str[i + 1] != '_')
		return (0);
	j = i + 2;
	while (str[j] != '\0')
	{
		if (ft_isalnum(str[j]) != 1 && str[j] != '_')
			return (0);
		j++;
	}
	return (1);
}

int	is_valid_var_start(char	*str, int i)
{
		if (str[i] == '$' 
			&& (str[i + 1] == '?'
			|| ft_isalpha(str[i + 1])
			|| str[i + 1] == '_'))
		{
			return (1);
		}
		return (0);
}

int	has_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}