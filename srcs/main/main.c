/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:53:42 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/17 10:53:43 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int			status;
	t_command	*commands;

	(void)argv;
	(void)argc;
	while (1)
	{
		commands = NULL;
		status = build_commands(&commands);
		if (status != CMD_SUCCESS)
			continue ;
		status = executor(commands, envp);
		free_command_arr(commands);
	}
	return (0);
}


