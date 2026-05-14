/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:24:46 by jisulim           #+#    #+#             */
/*   Updated: 2026/04/29 10:24:47 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(int code, char *path)
{
	if (code == ENOMEM)
		return (CMD_MALLOC_ERROR);
	write(2, "cd: ", 4);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, strerror(code), ft_strlen(strerror(code)));
	write(2, "\n", 1);
	return (1);
}

static int	cd_arg_error(void)
{
	write(2, "cd: too many arguments\n", 23);
	return (1);
}

static int	run_cd(t_shell *shell, char *path)
{
	char	*old_pwd;
	char	*new_pwd;
	int		status;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		return (cd_error(errno, path));
	if (chdir(path) != 0)
	{
		free(old_pwd);
		return (cd_error(errno, path));
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		free(old_pwd);
		return (cd_error(errno, path));
	}
	status = update_env(shell, "OLDPWD", old_pwd);
	if (status == CMD_SUCCESS)
		status = update_env(shell, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (status);
}

int	execute_cd(t_command *command, t_shell *shell)
{
	char	*path;
	int		home_index;
	int		oldpwd_index;

	if (command->argv[1] != NULL && command->argv[2] != NULL)
		return (cd_arg_error());
	if (command->argv[1] == NULL 
		|| (ft_strncmp(command->argv[1], "--", 2) == 0 
		&& ft_strlen(command->argv[1]) == 2))
	{
		home_index = find_envp_index(shell, "HOME");
		if (home_index == -1 || shell->envp[home_index][4] != '=')
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		path = &(shell->envp[home_index][5]);
		if (path[0] == '\0')
			return (0);
	}
	else if (ft_strncmp(command->argv[1], "-", 1) == 0 && ft_strlen(command->argv[1]) == 1)
	{
		oldpwd_index = find_envp_index(shell, "OLDPWD");
			if (oldpwd_index == -1 || shell->envp[oldpwd_index][6] != '=')
		{
			write(2, "cd: OLDPWD not set\n", 19);
			return (1);
		}
		path = &(shell->envp[oldpwd_index][7]);
		if (path[0] == '\0')
			return (0);
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
	else
		path = command->argv[1];
	return (run_cd(shell, path));
}
