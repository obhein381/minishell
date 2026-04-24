/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:26:18 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/30 12:26:20 by jisulim          ###   ########.fr       */
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
			return (NULL);
		if (*input)
			add_history(input);
	}
	else
		input = readline(NULL);
	return (input);
}

static int	handle_build_error(int status, t_token **token_arr, t_command **commands)
{
	if (*token_arr != NULL)
		free_token_arr(*token_arr);
	if (*commands != NULL)
		free_command_arr(*commands);
	*token_arr = NULL;
	*commands = NULL;
	if (status == PIPE_ERROR)
		write(2, "pipe error\n", 11);
	else if (status == REDIR_ERROR)
		write(2, "redir error\n", 12);
	return (status);
}

int	build_commands(t_command **commands, t_shell *shell)
{
	int		status;
	t_token	*token_arr;

	token_arr = NULL;
	*commands = NULL;
	shell->input = read_input();
	if (shell->input == NULL)
	{
		write(1, "exit\n", 5);
		return (CMD_EOF);
	}
	status = tokenization(shell->input, &token_arr);
	free(shell->input);
	if (status != CMD_SUCCESS)
		return (handle_build_error(status, &token_arr, commands));
	status = expander(shell, &token_arr);
	if (status != CMD_SUCCESS)
		return (handle_build_error(status, &token_arr, commands));
	status = parser(shell, token_arr, commands);
	if (status != CMD_SUCCESS)
		return (handle_build_error(status, &token_arr, commands));
	free_token_arr(token_arr);
	return (CMD_SUCCESS);
}
