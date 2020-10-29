/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:10:20 by seronen           #+#    #+#             */
/*   Updated: 2020/10/29 22:35:20 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		q_offer_path(t_lemin *node, t_queue *q, t_pipe *p)
{
	if (p->flow < 1 || q_check(node, q, p->room))
		return (0);
	if ( p->room->visited >= node->v_token)
		return (0);
	if (p->adj->room->id == node->end->id)
		return (0);
	else
		return (1);
}

int		mapped(t_lemin *node, t_room *r)
{
	if (r->id == node->start->id || r->id == node->end->id)
		return (1);
	if (r->mapped >= node->m_token)
		return (0);
	return (1);
}

int		retrace_path(t_lemin *node, t_parent *p, t_set *s)
{
	t_parent *tmp;
	t_room *r;
	t_path *path;
	int len;

	if (!p)
		ft_error("retrace_path: Cannot retrace, no parent!");
	path = NULL;
	tmp = p;
	r = tmp->from;
	add_path(&path, pathnew(node, tmp->room));
	add_path(&path, pathnew(node, r));
	len = 1;
	while (tmp->prev)
	{
		if (r->id == tmp->room->id)
		{
			r = tmp->from;
			if (!mapped(node, r))
				return (free_path(&path));
			add_path(&path, pathnew(node, r));
			len++;
		}
		tmp = tmp->prev;
	}
	path_to_set(path, &s->paths, len);
	return (1);
}

int		graph_path(t_lemin *node, t_queue *q, t_set *s)
{
	t_pipe *p;
	t_parent *par;

	q_add(&q, node->start);
	par = init_parent(node, node->start);
	while (q)
	{
		if (q->room->id == node->end->id)
			retrace_path(node, par, s);
		q_visit(node, q);
		p = q->room->pipes;
		while (p && q->room->id != node->end->id)
		{
			if (q_offer_path(node, q, p))
			{
				q_add(&q, p->room);
				q_parent(par, p);
			}
			p = p->next;
		}
		par = par->next;
		q = q_del(q);
	}
	free_parent(node, &node->parent); // Why intermittent segfault??
	if (!q)
		return (0);
	q_free(&q);
	return (1);
}
