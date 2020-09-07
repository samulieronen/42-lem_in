/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 09:48:22 by seronen           #+#    #+#             */
/*   Updated: 2019/11/14 16:24:51 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list *newlink;

	if (!(newlink = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		newlink->content = NULL;
		newlink->content_size = 0;
	}
	else
	{
		if (!(newlink->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(newlink->content, content, content_size);
		newlink->content_size = content_size;
	}
	newlink->next = NULL;
	return (newlink);
}
