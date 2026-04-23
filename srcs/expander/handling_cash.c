/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:40:02 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/22 13:40:03 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_f_str(char **f_str, char *word, int *i)
{
	int	j;

	*f_str = malloc(*i + 2);
	if (*f_str == NULL)
		return (CMD_MALLOC_ERROR);
	j = 0;
	while (j < *i)
	{
		(*f_str)[j] = word[j];
		j++;
	}
	(*f_str)[j] = '\0';
	(*i)++;
	return (CMD_SUCCESS);
}

int	make_env_var(char **env_var, char *word, int *i)
{
	int	j;

	*env_var = malloc(ft_strlen(word) + 1);
	if (*env_var == NULL)
		return (CMD_MALLOC_ERROR);
	j = 0;
	if (word[*i] == '?')
	{
		ft_strlcpy(*env_var, "?", 2);
		(*i)++;
		return (CMD_SUCCESS);
	}
	if (ft_isalpha(word[*i]) || word[*i] == '_')
	{
		while (ft_isalnum(word[*i]) || word[*i] == '_')
		{
			(*env_var)[j] = word[*i];
			j++;
			(*i)++;
		}
	}
	(*env_var)[j] = '\0';
	return (CMD_SUCCESS);
}

int	make_s_str(char **s_str, char *word, int *i)
{
	int j;

	*s_str = malloc(ft_strlen(word) + 1);
	if (*s_str == NULL)
		return (CMD_MALLOC_ERROR);
	(*s_str)[0] = '\0';
	j = 0;
	while (word[*i] != '\0')
	{
		(*s_str)[j] = word[*i];
		j++;
		(*i)++;
	}
	(*s_str)[j] = '\0';
	return (CMD_SUCCESS);
}

char	*all_str_join(char *f_str, char *env_var, char *s_str, int *i)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(f_str, env_var);
	if (temp == NULL)
		return (NULL);
	result = ft_strjoin(temp, s_str);
	if (result == NULL)
	{
		free(temp);
		return (NULL);
	}
	*i = ft_strlen(f_str) + ft_strlen(env_var);
	free(temp);
	return (result);
}

int	handling_cash(t_shell *shell, char **word, int *i)
{
	char	*f_str;
	char	*s_str;
	char	*env_var;
	char	*temp;
	int		state;

	init_cash(&f_str, &s_str, &env_var);
	state =  make_f_str(&f_str, *word, i);
	if (state != CMD_SUCCESS)
		return (handle_cash_free(state, f_str, s_str, env_var));
	state = make_env_var(&env_var, *word, i);
	if (state != CMD_SUCCESS)
		return (handle_cash_free(state, f_str, s_str, env_var));
	state = load_env(shell, &env_var);
	if (state != CMD_SUCCESS)
		return (handle_cash_free(state, f_str, s_str, env_var));
	state = make_s_str(&s_str, *word, i);
	if (state != CMD_SUCCESS)
		return (handle_cash_free(state, f_str, s_str, env_var));
	temp = all_str_join(f_str, env_var, s_str, i);
	if (temp == NULL)
		return (handle_cash_free(CMD_MALLOC_ERROR, f_str, s_str, env_var));
	free(*word);
	*word = temp;
	return (handle_cash_free(CMD_SUCCESS, f_str, s_str, env_var));
}
