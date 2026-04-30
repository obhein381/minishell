/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:09:09 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/30 11:09:10 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_valid(char *argv)
{
	int	i;

	if (argv[0] == '\0')
		return (1);
	if (ft_isalpha(argv[0]) != 1 && argv[0] != '_')
		return (1);
	i = 1;
	while (argv[i] != '\0')
	{
		if (ft_isalnum(argv[i]) != 1 && argv[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	remove_var(t_shell *shell, int target_index)
{
	free(shell->envp[target_index]);
	while (shell->envp[target_index + 1] != NULL)
	{
		shell->envp[target_index] = shell->envp[target_index + 1];
		target_index++;
	}
	shell->envp[target_index] = NULL;
}

int	execute_unset(t_command *command, t_shell *shell)
{
	char	**argv;
	int		i;
	int		envp_index;
	int		exit_code;

	exit_code = 0;
	argv = command->argv;
	i = 1;
	while (argv[i] != NULL)
	{
		if (check_valid(argv[i]) == 1)
		{
			write(2, "unset: `", 8);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "': not a valid identifier\n", 26);
			exit_code = 1;
			i++;
			continue ;
		}
		envp_index = find_envp_index(shell, argv[i]);
		if (envp_index == -1)
		{
			i++;
			continue ;
		}
		remove_var(shell, envp_index);
		i++;
	}
	return (exit_code);
}
