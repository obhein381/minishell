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

static char	*read_input(void)
{
	char	*input;

	if (isatty(STDIN_FILENO))
	{
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		if (*input)
			add_history(input);
	}
	else
		input = readline(NULL);
	return (input);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = read_input();
	}
	return (0);
}


