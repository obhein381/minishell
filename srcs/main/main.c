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

static void	free_all(char *input, t_token *token_arr, t_command *commands)
{
	if (input != NULL)
		free(input);
	if (token_arr != NULL)
		free_token_arr(token_arr);
	if (commands != NULL)
		free_command_arr(commands);
}

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
	char		*input;
	t_token		*token_arr;
	t_command	*commands;

	while (1)
	{
		commands = NULL;
		input = read_input();
		token_arr = tokenization(input);
		if (token_arr == NULL)
		{
			free_all(input, token_arr, commands);
			write(2, "malloc error\n", 13);
			return(1);
		}
		commands = parser(token_arr);
		if (commands == NULL)
		{
			free_all(input, token_arr, commands);
			continue ;
		}
		free_all(input, token_arr, commands);
	}
	return (0);
}


