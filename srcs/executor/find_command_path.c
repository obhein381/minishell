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

int	find_command_path(char *command, char **envp, char **path)
{
	(void)envp;
	*path = NULL;
	if (ft_strchr(command, '/'))
		return (handle_slash_command(command, path));
	//get non slash commnad path
	return (CMD_NOT_FOUND);
}
