/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:44:48 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/25 16:44:51 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_slash_command(char *command, char **path)
{
	if (access(command, X_OK) == 0)
	{
		*path = ft_strdup(command);
		if (*path == NULL)
			return (CMD_MALLOC_ERROR);
		return (CMD_SUCCESS);
	}
	if (errno == EACCES)
		return (CMD_PERMISSION);
	return (CMD_NOT_FOUND);
}

int	get_path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	free_dirs(char **dirs)
{
	int i;

	i = 0;
	if (dirs[i] != NULL)
		return ;
	while (dirs[i] != NULL)
		free(dirs[i++]);
	free(dirs);
}

char	**make_dirs(char *command, char *path)
{
	char	**dirs;
	char	*tmp;
	char	*full;
	int		i;

	dirs = ft_split(path, ':');
	if (dirs == NULL)
		return (NULL);
	i = 0;
	while (dirs[i] != NULL)
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (tmp == NULL)
			return (free_dirs(dirs), NULL);
		full = ft_strjoin(tmp, command);
		free(tmp);
		if (full == NULL)
			return (free_dirs(dirs), NULL);
		free(dirs[i]);
		dirs[i] = full;
		i++;
	}
	return (dirs);
}

int	find_cmd_input_path(char **dirs, char **path)
{
	int	i;

	i = 0;
	while (dirs[i] != NULL)
	{
		if (access(dirs[i], X_OK) == 0)
		{
			*path = ft_strdup(dirs[i]);
			if (*path == NULL)
				return (CMD_MALLOC_ERROR);
			return (CMD_SUCCESS);
		}
		i++;
	}
	return (CMD_NOT_FOUND);
}

