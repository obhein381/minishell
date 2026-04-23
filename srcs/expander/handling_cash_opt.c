/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cash_opt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:20:47 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/23 12:20:49 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	load_env(t_shell *shell, char **env_var)
{
	int		i;
	int		j;

	i = 0;
	if ((*env_var)[0] == '?' && (*env_var)[1] == '\0')
	{
		free(*env_var);
		*env_var = ft_itoa(shell->exit_status);
		if (*env_var == NULL)
			return (CMD_MALLOC_ERROR);
		return (CMD_SUCCESS);
	}
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
	free(*env_var);
	*env_var = ft_strdup("");
	if (*env_var == NULL)
		return (CMD_MALLOC_ERROR);
	return (CMD_SUCCESS);
}

void init_cash(char **f_str, char **s_str, char **env_var)
{
	*f_str = NULL;
	*s_str = NULL;
	*env_var = NULL;
}

int	handle_cash_free(int state, char *f_str, char *s_str, char *env_var)
{
	if (f_str != NULL)
		free(f_str);
	if (s_str != NULL)
		free(s_str);
	if (env_var != NULL)
		free(env_var);
	return (state);
}

