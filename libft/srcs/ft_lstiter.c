/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:26:47 by seronen           #+#    #+#             */
/*   Updated: 2019/11/03 11:55:44 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *tmp;

	if (lst && f)
	{
		tmp = lst;
		while (tmp)
		{
			f(tmp);
			tmp = tmp->next;
		}
	}
}
