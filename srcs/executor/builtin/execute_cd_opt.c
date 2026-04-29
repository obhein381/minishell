/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:05:31 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/29 14:05:32 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_envp_index(t_shell *shell, char *target)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(target);
	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(target, shell->envp[i], len) == 0 
		&& shell->envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	add_target_env(t_shell *shell, char *result)
{
	char	**new_envp;
	int		i;

	new_envp = dup_envp(shell->envp);
	if (new_envp == NULL)
		return (CMD_MALLOC_ERROR);
	free(shell->envp);
	i = 0;
	while (new_envp[i] != NULL)
		i++;
	new_envp[i] = result;
	i++;
	new_envp[i] = NULL;
	shell->envp = new_envp;
	return (CMD_SUCCESS);
}

int	update_env(t_shell *shell, char *target, char *value)
{
	char	*result;
	char	*temp;
	int		envp_index;
	int		status;

	temp = ft_strjoin(target, "=");
	if (temp == NULL)
		return (CMD_MALLOC_ERROR);
	result = ft_strjoin(temp, value);
	free(temp);
	if (result == NULL)
		return (CMD_MALLOC_ERROR);
	envp_index = find_envp_index(shell, target);
	if (envp_index == -1)
	{
		status = add_target_env(shell, result);
		if (status != CMD_SUCCESS)
			free(result);
		return (status);
	}
	free(shell->envp[envp_index]);
	shell->envp[envp_index] = result;
	return (CMD_SUCCESS);
}
