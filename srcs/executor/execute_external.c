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

static int	get_error_code(int err)
{
	if (err == ENOENT)
		return (127);
	else if (err == EACCES)
		return (126);
	else
		return (1);
}

static int	handling_error(char *command, char *path)
{
	perror(command);
	if (path != NULL)
		free(path);
	return (1);
}

int	execute_external(t_command *commands, char **envp)
{
	char	*path;
	pid_t	pid;
	int		status;

	status = find_command_path(commands->argv[0], envp, &path);
	if (status != CMD_SUCCESS)
		return (status);
	pid = fork();
	if (pid < 0)
		return (handling_error("fork", path));
	if (pid == 0)
	{
		if (execve(path, commands->argv, envp) == -1)
		{
			perror("execve");
			exit(get_error_code(errno));
		}
	}
	if (waitpid(pid, &status, 0) < 0)
		return (handling_error("waitpid", path));
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

