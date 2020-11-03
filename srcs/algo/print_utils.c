/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:29:08 by seronen           #+#    #+#             */
/*   Updated: 2020/11/03 12:31:28 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_antnbr(t_lemin *node)
{
	node->antnbr++;
	return (node->antnbr);
}

int		init_print(t_lemin *node, t_pathf *paths)
{
	t_pathf *p;
	int		*new;

	p = paths;
	node->antnbr = 0;
	node->steps = 1;
	node->goaled = 0;
	while (p)
	{
		p->id_arr = NULL;
		if (!(new = (int*)malloc(sizeof(int) * p->len + 2)))
			ft_error("init_print: Malloc failed!", NULL, 0);
		ft_bzero(new, sizeof(int) * p->len + 2);
		if (p->res > 0)
		{
			new[0] = get_antnbr(node);
			p->res--;
		}
		p->id_arr = new;
		p = p->next;
	}
	return (0);
}
