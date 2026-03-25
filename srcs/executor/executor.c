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

int	executor(t_command *commands, char **envp)
{
	int	builtin_type;

	if (commands == NULL)
		return (1);
	builtin_type = get_builtin_type(commands);
	if (builtin_type == UNKNOWN_COMMAND)
		execute_external(commands, envp);
	else
		execute_builtin(commands, builtin_type);
	return (0);
}

