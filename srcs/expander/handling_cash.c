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

int	load_env(t_shell *shell, char **env_var)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (shell->envp[i] != NULL)
	{
		j = 0;
		while(shell->envp[i][j] != '\0' && shell->envp[i][j] != '=')
		{
			if((*env_var)[j] != shell->envp[i][j])
				break ;
			j++;
		}
		if (shell->envp[i][j] == '=' && (*env_var)[j] == '\0')
		{
			free(*env_var);
			*env_var = ft_strdup(&(shell->envp[i][j + 1]));
			if (*env_var == NULL)
				return (CMD_MALLOC_ERROR);
			return (CMD_SUCCESS);
		}
		i++;
	}
	result = ft_strjoin("$", *env_var);
	if (result == NULL)
		return (CMD_MALLOC_ERROR);
	free(*env_var);
	*env_var = result;
	return (CMD_SUCCESS);
}

int	handling_cash(t_shell *shell, char **word, int *i)
{
	char	*f_str;
	char	*s_str;
	char	*env_var;
	char	*temp;
	int		j;
	int		state;

	f_str = malloc(*i + 2);
	if (f_str == NULL)
		return (CMD_MALLOC_ERROR);
	j = 0;
	while(j < *i)
	{
		f_str[j] = (*word)[j];
		j++;
	}
	f_str[j] = '\0';
	(*i)++;
	env_var = malloc(ft_strlen(*word) + 1);
	if (env_var == NULL)
	{
		free(f_str);
		return (CMD_MALLOC_ERROR);
	}
	j = 0;
	while ((*word)[*i] != '\0' && (*word)[*i] != ' ' && (*word)[*i] != '\t' && (*word)[*i] != '\"')
	{
		env_var[j] = (*word)[*i];
		j++;
		(*i)++;
	}
	env_var[j] = '\0';
	state = load_env(shell, &env_var);
	if (state != CMD_SUCCESS)
	{
		free(f_str);
		free(env_var);
		return (CMD_MALLOC_ERROR);
	}
	s_str = malloc(ft_strlen(*word) + 1);
	if (s_str == NULL)
	{
		free(f_str);
		free(env_var);
		return (CMD_MALLOC_ERROR);
	}
	s_str[0] = '\0';
	j = 0;
	while ((*word)[*i] != '\0')
	{
		s_str[j] = (*word)[*i];
		j++;
		(*i)++;
	}
	s_str[j] = '\0';
	temp = NULL;
	temp = ft_strjoin(f_str, env_var);
	if (temp == NULL)
	{
		free(f_str);
		free(env_var);
		free(s_str);
		return (CMD_MALLOC_ERROR);
	}
	free(*word);
	*word = ft_strjoin(temp, s_str);
	if (*word == NULL)
	{
		free(f_str);
		free(s_str);
		free(temp);
		free(env_var);
		return (CMD_MALLOC_ERROR);
	}
	*i = ft_strlen(f_str) + ft_strlen(env_var);
	free(f_str);
	free(env_var);
	free(s_str);
	free(temp);
	return (CMD_SUCCESS);
}
