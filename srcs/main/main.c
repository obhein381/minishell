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
#include <stdio.h>

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
	t_token	*token_arr;

	while (1)
	{
		input = read_input();
		token_arr = tokenization(input);
		print_token_arr(token_arr);
		if (token_arr == NULL)
			return (1);
	}
	return (0);
}


