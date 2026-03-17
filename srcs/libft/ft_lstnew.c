/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:25:50 by jisulim           #+#    #+#             */
/*   Updated: 2025/10/25 14:39:30 by jisulim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*make;

	make = malloc(sizeof(t_list));
	if (make == NULL)
		return (NULL);
	make->content = content;
	make->next = NULL;
	return (make);
}
