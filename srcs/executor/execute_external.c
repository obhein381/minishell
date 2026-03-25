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

int	execute_external(t_command *commands, char **envp)
{
	// find command path
	// fork
	// child -> execve
	// parent -> wait
	(void)commands;
	(void)envp;

	return (0);
}

