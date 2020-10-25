/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:10:20 by seronen           #+#    #+#             */
/*   Updated: 2020/10/25 15:55:28 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		q_offer_path(t_lemin *node, t_queue *q, t_pipe *p)
{
	if ( p->flow < 1 || p->room->visited == node->v_token || q_check(q, p->room))
	{
//		ft_printf("Offer rejected for edge %s – %s\n", p->adj->room->name, p->room->name);
		return (0);
	}		
	else
	{
//		ft_printf("Offer accepted for edge %s – %s\n", p->adj->room->name, p->room->name);
		return (1);
	}
}

int		graph_path(t_lemin *node, t_queue *q)
{
	t_pipe *p;

	q_add(&q, node->start);
	ft_printf("PATH MODE\n");
	while (q)
	{
		q_visit(q);
		p = q->room->pipes;
		while (p)
		{
			if (q_offer_path(node, q, p))
			{
				q_add(&q, p->room);
			}
			p = p->next;
		}
		q = q_del(q);
	}
	return (0);
}

int     path()
{
    
    return (0);
}