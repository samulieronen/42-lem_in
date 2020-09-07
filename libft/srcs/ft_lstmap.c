/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:36:39 by seronen           #+#    #+#             */
/*   Updated: 2019/11/03 11:37:42 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *head;
	t_list *res;
	t_list *link;

	if (!lst || !f)
		return (NULL);
	link = f(lst);
	if (!(res = ft_lstnew(link->content, link->content_size)))
		return (NULL);
	lst = lst->next;
	head = res;
	while (lst)
	{
		link = f(lst);
		if (!(res->next = ft_lstnew(link->content, link->content_size)))
			return (NULL);
		res = res->next;
		lst = lst->next;
	}
	return (head);
}
