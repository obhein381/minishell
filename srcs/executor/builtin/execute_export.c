/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:39:18 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/31 11:39:20 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	input_key(t_shell *shell,char *entry,  int key_index)
{
	int		key_envp_index;
	char	**new_envp;

	key_envp_index = find_key_envp(shell->envp, entry, key_index);
	if (key_envp_index != -1)
	{
		free (shell->envp[key_envp_index]);
		shell->envp[key_envp_index] = entry;
		return (CMD_SUCCESS);
	}
	key_envp_index = envp_len(shell->envp);
	shell->envp[key_envp_index] = entry;
	shell->envp[key_envp_index + 1] = NULL;
	new_envp = dup_envp(shell->envp);
	if (new_envp == NULL)
	{
		shell->envp[key_envp_index] = NULL;
		free(entry);
		return (CMD_MALLOC_ERROR);
	}
	free_envp(shell->envp, envp_len(shell->envp));
	shell->envp = new_envp;
	return (CMD_SUCCESS);
}

static int	handle_error(int key_index, int *i, char *argv, int *status)
{
	if (key_index == -1)
	{
		(*i)++;
		return (1);
	}
	if (check_key(argv, key_index) == 1)
	{
		write(2, "export: not an identifier: ",  27);
		write(2, argv, ft_strlen(argv));
		write(2, "\n", 1);
		*status = CMD_FAILURE;
		(*i)++;
		return (1);
	}
	return (0);
}

int	execute_export(t_shell *shell)
{
	char	**argv;
	char	*entry;
	int		i;
	int		key_index;
	int		status;

	if (shell == NULL || shell->envp == NULL || shell->commands == NULL
		|| shell->commands->argv == NULL)
		return (CMD_SUCCESS);
	argv = shell->commands->argv;
	if (argv[1] == NULL)
		return(execute_env(shell));
	status = CMD_SUCCESS;
	i = 1;
	while (argv[i] != NULL)
	{
		key_index = find_key_index(argv[i]);
		if (handle_error(key_index, &i, argv[i], &status) == 1)
			continue ;
		entry = ft_strdup(argv[i]);
		if (entry == NULL || input_key(shell, entry, key_index) == CMD_MALLOC_ERROR)
			return (CMD_MALLOC_ERROR);
		i++;
	}
	return (status);
}