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

static int	get_error_code(int err)
{
	if (err == ENOENT)
		return (CMD_NOT_FOUND);
	else if (err == EACCES)
		return (CMD_PERMISSION);
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

static int	print_signal_error(int status)
{
	int	sig;

	if (!WIFSIGNALED(status))
		return (1);
	sig = WTERMSIG(status);
	if (sig == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	else if (sig == SIGINT)
		write(2, "\n", 1);
	return (128 + WTERMSIG(status));
}

static int	apply_redirection(t_command *command)
{
	if (command->fd_in != -1)
	{
		if (dup2(command->fd_in, STDIN_FILENO) < 0)
		{
			close(command->fd_in);
			return (-1);
		}
		close(command->fd_in);
	}
	if (command->fd_out != -1)
	{
		if (dup2(command->fd_out, STDOUT_FILENO) < 0)
		{
			close(command->fd_out);
			return (-1);
		}
		close(command->fd_out);
	}
	return (0);
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
		set_signal_child();
		if (apply_redirection(commands) < 0)
		{
			perror("dup2");
			free(path);
			exit(get_error_code(errno));
		}
		if (execve(path, commands->argv, envp) == -1)
		{
			free(path);
			perror("execve");
			exit(get_error_code(errno));
		}
	}
	set_signal_parent_wait();
	if (waitpid(pid, &status, 0) < 0)
	{
		set_signal_prompt();
		return (handling_error("waitpid", path));
	}
	free(path);
	set_signal_prompt();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (print_signal_error(status));
}

