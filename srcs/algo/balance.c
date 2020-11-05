/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:49:49 by seronen           #+#    #+#             */
/*   Updated: 2020/11/05 16:43:08 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			total_ants(t_set *s)
{
	t_pathf *p;
	int		total;

	p = s->paths;
	total = 0;
	while (p)
	{
		if (p->res < 0)
			p->res = 0;
		total += p->res;
		p = p->next;
	}
	return (total);
}

int					balance_ants(t_lemin *node, t_set *s)
{
	int		total;
	t_pathf *p;

	if (!s)
		ft_error("No set to balance!", NULL, 0);
	if (!(total = total_ants(s)))
		ft_error("total value incorrect!", NULL, 0);
	while (total > node->antcount)
	{
		p = s->paths;
		while (p && total > node->antcount)
		{
			if (p->res > 0)
			{
				p->res--;
				total--;
			}
			p = p->next;
		}
	}
	return (0);
}
