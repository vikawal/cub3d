/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:47:38 by vmyshko           #+#    #+#             */
/*   Updated: 2023/11/03 17:26:01 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	if (lst == NULL || del == NULL)
		return ;
	head = *lst;
	while (head)
	{
		tmp = head ->next;
		(*del)(head ->content);
		free(head);
		head = tmp;
	}
	*lst = NULL;
}
