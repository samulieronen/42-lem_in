/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:10:20 by seronen           #+#    #+#             */
/*   Updated: 2020/10/25 00:16:27 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		graph_path(t_lemin *node, t_queue *q)
{
	t_pipe *p;

	q_add(&q, node->start);
	while (q)
	{
		if (q->room->id == node->end->id)
			break ;
		q_visit(q);
		p = q->room->pipes;
		while (p)
		{
			if (q_offer(node, q, p))
				q_add(&q, p->room);
			p = p->next;
		}
		q = q_del(q);
	}
	if (!q)
		ft_error("graph_path exited with error code 1: No queue!");
	return (0);
}

int     path()
{
    
    return (0);
}