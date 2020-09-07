/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 10:47:07 by seronen           #+#    #+#             */
/*   Updated: 2019/10/31 10:47:09 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *temp;
	t_list *tempnext;

	temp = *alst;
	while (temp)
	{
		tempnext = temp->next;
		del(temp->content, temp->content_size);
		free(temp);
		temp = tempnext;
	}
	*alst = NULL;
}
