/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:14:41 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/25 17:25:28 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*box;
	t_list	*box2;

	if (lst == NULL || del == NULL)
		return ;
	box = *lst;
	while (box != NULL)
	{
		del(box->content);
		box2 = box;
		box = box->next;
		free(box2);
	}
	*lst = NULL;
}
