/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:18:01 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/25 12:18:02 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	execute_external(t_command *commands, char **envp)
{
	char	*path;
	int		status;

	status = find_command_path(commands->argv[0], envp, &path);
	if (status != CMD_SUCCESS)
		return (status);
	// find command path
	// fork
	// child -> execve
	// parent -> wait
	free(path);
	return (0);
}

