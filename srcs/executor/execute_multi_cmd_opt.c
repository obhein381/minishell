/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi_cmd_opt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:18:11 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/07 13:18:12 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int convert_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_external_child(t_shell *shell, t_command *command)
{
	char		**envp;
	char		*path;
	int			status;

	envp = shell->envp;
	 status = find_command_path(command->argv[0], envp, &path);
	 if (status != CMD_SUCCESS)
	 	exit(status);
	execve(path, command->argv, envp);
	perror("execve");
	exit(1);
}

int	wait_all_child(t_command *commands)
{
	int	status;

	while (commands != NULL)
	{
		if (waitpid(commands->pid, &status, 0) == -1)
		{
			if (errno == EINTR)
				continue ;
			perror("waitpid");
		}
		commands = commands->next;
	}
	return (convert_exit_status(status));
}

void	close_all_fd(int *fd)
{
	if (fd == NULL)
		return ;
	close(fd[0]);
	close(fd[1]);
}