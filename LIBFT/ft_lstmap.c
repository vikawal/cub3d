/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:00:46 by vmyshko           #+#    #+#             */
/*   Updated: 2024/12/10 17:58:37 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;
	void	*content_new;
	int		i;

	i = 1;
	head = NULL;
	while (lst)
	{
		content_new = f(lst->content);
		tmp = ft_lstnew(content_new);
		if (!tmp)
		{
			ft_lstclear(&head, del);
			del(content_new);
			return (NULL);
		}
		ft_lstadd_back(&head, tmp);
		lst = lst->next;
	}
	return (head);
}

// #include "libft.h"

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new_list;
// 	t_list	*new_node;
// 	void	*new_content;

// 	new_list = NULL;
// 	while (lst != NULL)
// 	{
// 		new_content = f(lst->content);
// 		new_node = ft_lstnew(new_content);
// 		if (new_node == NULL)
// 		{
// 			ft_lstclear(&new_list, del);
// 			del(new_content);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&new_list, new_node);
// 		lst = lst->next;
// 	}
// 	return (new_list);
// }