/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:22:39 by jisulim           #+#    #+#             */
/*   Updated: 2026/05/06 11:22:41 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"

long long	ft_atoll(const char *str, int *status)
{
	int			i;
	int			check;
	long long	result;
	int			digit;

	result = 0;
	check = 1;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			check = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > (LLONG_MAX - digit) / 10)
		{
			*status = 1;
			return (0);
		}
		result = (result * 10) + (digit);
		i++;
	}
	return (check * result);
}

static int	handling_error(t_shell *shell, char *argv, int status)
{
	if (status == 1)
	{
		write(2, "exit: too many arguments\n", 26);
		return (1);
	}
	else
	{
		write(2, "exit: ",  6);
		write(2, argv, ft_strlen(argv));
		write(2, ": numeric argument required\n", 28);
		shell->shut_down = 1;
		return (2);
	}
}

static int is_numeric(char *str)
{
	int	i;

	if (str[0] == '+' || str[0] == '-')
		i = 1;
	else
		i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


int	execute_exit(t_command *command, t_shell *shell)
{
	long long	status;
	int			sign;

	sign = 0;
	if (command->argv[1] == NULL)
	{
		shell->shut_down = 1;
		return (shell->exit_status);
	}
	if (is_numeric(command->argv[1]) == 0)
		return (handling_error(shell, command->argv[1], 2));
	if (command->argv[2] != NULL)
		return (handling_error(shell, command->argv[1], 1));
	if (ft_strlen(command->argv[1]) == 20
	&& ft_strncmp(command->argv[1], "-9223372036854775808", 20) == 0)
	{
		shell->shut_down = 1;
		return ((unsigned char)LLONG_MIN);
	}
	shell->shut_down = 1;
	status = ft_atoll(command->argv[1], &sign);
	if (sign == 1)
		return (handling_error(shell, command->argv[1], 2));
	return ((unsigned char)status);
}

