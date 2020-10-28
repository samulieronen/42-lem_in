/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:10:20 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 16:20:56 by seronen          ###   ########.fr       */
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

t_path	*path_new(t_room *r)
{
	t_path *new;

	new = (t_path*)malloc(sizeof(t_path));
	if (!new)
		ft_error("path_new: Malloc failed!");
	if (!r)
		ft_error("path_new: no room to add!");
	new->r = r;
	new->next = NULL;
	return (new);
}

int		_add_path(t_path **alst, t_path *new)
{
	if (*alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	else if (new)
		*alst = new;
	return (0);
}

int		path_to_set(t_path *head, t_pathf **alst, int len)
{
	t_pathf *new;

	new = (t_pathf*)malloc(sizeof(t_pathf));
	new->path = head;
	new->len = len;
	if (!new)
		ft_error("path_to_set: Malloc failed!");
	if (*alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	if (new)
		*alst = new;
	return (0);
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
	_add_path(&path, path_new(tmp->room));
	_add_path(&path, path_new(r));
	len = 1;
	while (tmp->prev)
	{
		if (r->id == tmp->room->id)
		{
			r = tmp->from;
			if (!mapped(node, r))
				return (0);
			r->mapped = node->m_token;
			_add_path(&path, path_new(r));
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
	t_queue *q_head;

	q_add(&q, node->start);
	par = init_parent(node->start);
	head = par;
	q_head = q;
	while (q)
	{
		if (q->room->id == node->end->id)
			retrace_path(node, par, s, flow);
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
