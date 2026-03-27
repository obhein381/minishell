/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:26:12 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/27 11:26:13 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	check_option_n(char *argv)
{
	int i;

	if (argv == NULL)
		return (0);
	if (argv[0] != '-')
		return (0);
	if (argv[1] == '\0')
		return (0);
	i = 1;
	while (argv[i] != '\0')
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_argv(char **argv, int i)
{
	while (argv[i] != NULL)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	return ;
}

int	execute_echo(t_command *commands)
{
	char	**argv;
	int		opt_n;
	int		i;

	argv = commands->argv;
	i = 1;
	opt_n = 0;
	if (check_option_n(argv[i]) == 1)
	{
		opt_n = 1;
		while (argv[i] != NULL && check_option_n(argv[i]) == 1)
			i++;
	}
	print_argv(argv, i);
	if (opt_n == 0)
		write(1, "\n", 1);
	return (CMD_SUCCESS);
}