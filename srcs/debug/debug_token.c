/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:36:15 by jisulim           #+#    #+#             */
/*   Updated: 2026/03/17 14:37:09 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>


void	print_token_arr(t_token *token_arr)
{
	t_token *head;
	int		n;

	n = 0;
	head = token_arr;
	while (head != NULL)
	{
		printf("token %d value = %s\n", n, head->value);
		n++;
		head = head->next;
	}
	return ;

}
