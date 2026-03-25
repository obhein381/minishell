/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:10:16 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/25 14:10:18 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_command_path(char *command, char **envp, char **path)
{
	int		path_index;
	char	**dirs;
	int		i;
	int		status;

	*path = NULL;
	if (ft_strchr(command, '/'))
		return (handle_slash_command(command, path));
	path_index = get_path_index(envp);
	if (path_index == -1)
		return (CMD_NOT_FOUND);
	dirs = make_dirs(command, &envp[path_index][5]);
	if (dirs == NULL)
		return (CMD_MALLOC_ERROR);
	status = find_cmd_input_path(dirs, path);
	i = 0;
	free_dirs(dirs);
	return (status);
}
