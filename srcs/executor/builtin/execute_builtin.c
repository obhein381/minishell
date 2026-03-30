/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:03:34 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/25 13:03:36 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	call_cmd(t_command *commands, int type)
{
	int	status;

	status = CMD_UNKNOWN_ERR;
	if (type == COMMAND_ECHO)
		status = execute_echo(commands);
	/*if (type == COMMAND_CD)
	if (type == COMMAND_PWD)
	if (type == COMMAND_EXPORT)
	if (type == COMMAND_UNSET)
	if (type == COMMAND_ENV)
	if (type == COMMAND_EXIT)
	if (type == COMMAND_MIN_N)*/
	return (status);
}

int	execute_builtin(t_shell *shell, int type)
{
	int	status;

	status = call_cmd(shell->commands, type);
	if (status != CMD_SUCCESS)
		return (status);


	return (0);
}
