/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:10:20 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 21:40:08 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		q_offer_path(t_lemin *node, t_queue *q, t_pipe *p)
{
	if (p->flow < 1 || p->room->visited >= node->v_token || q_check(node, q, p->room))
		return (0);
	if (p->adj->room->id == node->end->id)
		return (0);
	else
		return (1);
}

int		mapped(t_lemin *node, t_room *r)
{
	if (r->id == node->start->id)
		return (1);
	if (r->id == node->end->id)
		return (1);
	if (r->mapped >= node->m_token)
		return (0);
	return (1);
}

int		retrace_path(t_lemin *node, t_parent *p, t_set *s, int *flow)
{
	t_parent *tmp;
	t_room *r;
	t_path *path;
	int len;

	if (!p)
		return (0);
	path = NULL;
	tmp = p;
	r = tmp->from;
	r->mapped = node->m_token;
	add_path(&path, path_new(tmp->room));
	add_path(&path, path_new(r));
	len = 1;
	while (tmp->prev)
	{
		if (r->id == tmp->room->id)
		{
			r = tmp->from;
			if (!mapped(node, r))
				return (0);
			r->mapped = node->m_token;
			add_path(&path, path_new(r));
			len++;
		}
		tmp = tmp->prev;
	}
	path_to_set(path, &s->paths, len);
	if (!PRINT_PATHS)
		return (1);
	while (path)
	{
		ft_printf("'%s' ", path->r->name);
		path = path->next;
	}
	ft_printf("\n");
	return (1);
}

int		graph_path(t_lemin *node, t_queue *q, t_set *s, int *flow)
{
	t_pipe *p;
	t_parent *par;
	t_parent *head;

	q_add(&q, node->start);
	par = init_parent(node->start);
	head = par;
	while (q)
	{
		if (q->room->id == node->end->id)
			retrace_path(node, par, s, flow);
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
	if (!q)
		return (0);
	q_free(q);
	return (1);
}
