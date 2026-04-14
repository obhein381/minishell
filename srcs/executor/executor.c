/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:19:48 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/24 14:19:51 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_builtin_type(t_command *commands)
{
	char	*s;
	int		type;
	int		len;

	s = commands->argv[0];
	len = ft_strlen(s);
	type = UNKNOWN_COMMAND;
	if (ft_strncmp(s, "echo", 4) == 0 && len == 4)
		type = COMMAND_ECHO;
	else if (ft_strncmp(s, "cd", 2) == 0 && len == 2)
		type = COMMAND_CD;
	else if (ft_strncmp(s, "pwd", 3) == 0 && len == 3)
		type = COMMAND_PWD;
	else if (ft_strncmp(s, "export", 6) == 0 && len == 6)
		type = COMMAND_EXPORT;
	else if (ft_strncmp(s, "unset", 5) == 0 && len == 5)
		type = COMMAND_UNSET;
	else if (ft_strncmp(s, "env", 3) == 0 && len == 3)
		type = COMMAND_ENV;
	else if (ft_strncmp(s, "exit", 4) == 0 && len == 4)
		type = COMMAND_EXIT;
	return (type);
}

static int	handle_executor_error(int status)
{
	if (status == MALLOC_ERROR)
	{
		write(2, "malloc error\n", 13);
		exit(1);
	}
	return (status);
}

int	execute_single_cmd(t_command *command, t_shell *shell)
{
	int	builtin_type;
	int	status;

	builtin_type = get_builtin_type(command);
	if (builtin_type == UNKNOWN_COMMAND)
		status = execute_external(command, shell->envp);
	else
		status = execute_builtin(command, shell, builtin_type);
	return (status);
}

int	executor(t_shell *shell)
{
	t_command	*commands;

	int	status;

	commands = shell->commands;
	if (commands == NULL)
		return (NO_COMMAND);
	if (commands->argv == NULL || commands->argv[0] == NULL)
		return (CMD_UNKNOWN_ERR);
	if (commands->next == NULL)
		status = execute_single_cmd(commands, shell);
	else
		status = execute_multi_cmd(shell);
	if (status != CMD_SUCCESS)
		return (handle_executor_error(status));
	return (CMD_SUCCESS);
}

