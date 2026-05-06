/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:22:39 by jisulim           #+#    #+#             */
/*   Updated: 2026/05/06 11:22:41 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handling_error(t_shell *shell, char *argv, int status)
{
	if (status == 1)
	{
		write(2, "exit: too many arguments\n", 26);
		return (status);
	}
	else
	{
		write(2, "exit: ",  6);
		write(2, argv, ft_strlen(argv));
		write(2, ": numeric argument required\n", 28);
		shell->shut_down = 1;
		return (status);
	}
}

static int is_numeric(char *str)
{
	int	i;

	if (str[0] == '+' || str[0] == '-')
		i = 1;
	else
		i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	execute_exit(t_command *command, t_shell *shell)
{
	int	status;

	if (command->argv[1] == NULL)
	{
		shell->shut_down = 1;
		return (shell->exit_status);
	}
	if (is_numeric(command->argv[1]) == 0)
		return (handling_error(shell, command->argv[1], 2));
	if (command->argv[2] != NULL)
		return (handling_error(shell, command->argv[1], 1));
	shell->shut_down = 1;
	status = ft_atoi(command->argv[1]);
	return (status);
}

