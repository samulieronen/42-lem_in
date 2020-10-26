/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:10:20 by seronen           #+#    #+#             */
/*   Updated: 2020/10/26 18:00:58 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		q_offer_path(t_lemin *node, t_queue *q, t_pipe *p, t_queue *head)
{
	if (p->flow < 1 || p->room->visited >= node->v_token || q_check(node, head, p->room))
	{
//		ft_printf("Offer rejected for edge %s – %s\n", p->adj->room->name, p->room->name);
		return (0);
	}
	if (p->adj->room->id == node->end->id)
		return (0);
	else
	{
//		ft_printf("Offer accepted for edge %s – %s\n", p->adj->room->name, p->room->name);
		return (1);
	}
}

int		retrace_path(t_lemin *node, t_parent *p)
{
	t_parent *tmp;
	t_room *r;

	if (!p)
		return (0);
	tmp = p;
	r = tmp->from;
//	calc_flow(tmp->from, tmp->room);
	ft_printf("%s  ", tmp->room->name);
	ft_printf("%s  ", r->name);
	while (tmp->prev)
	{
		if (r->id == tmp->room->id)
		{
			r = tmp->from;
			ft_printf("%s  ", r->name);
//			calc_flow(r, tmp->room);
		}
		tmp = tmp->prev;
	}
	ft_printf("\n");
	return (1);
}

int		graph_path(t_lemin *node, t_queue *q)
{
	t_pipe *p;
	t_parent *par;
	t_parent *head;
	t_queue *q_head;

	q_add(&q, node->start);
	par = init_parent(node->start);
	head = par;
	q_head = q;
	while (q)
	{
		if (q->room->id == node->end->id)
		{
			retrace_path(node, par);
		}
		q_visit(node, q);
		p = q->room->pipes;
		while (p && q->room->id != node->end->id)
		{
			if (q_offer_path(node, q, p, q_head))
			{
				q_add(&q, p->room);
				q_parent(par, p->room);
			}
			p = p->next;
		}
		par = par->next;
		q = q->next;
	//	q = q_del(q);
	}
	if (!q)
		return (0);
	return (1);
}

int     path()
{
    
    return (0);
}