/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:26:59 by seronen           #+#    #+#             */
/*   Updated: 2020/11/02 18:58:22 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pipe		*get_last(t_parent *prev, t_room *to)
{
	t_parent 	*p;
	t_pipe		*pipe;

	if (!prev)
		return (NULL);
	p = fetch_parent(prev, to);
	if (!p)
		return (NULL);
	pipe = p->from->pipes;
	while (pipe)
	{
		if (pipe->room->id == to->id)
			return (pipe);
		pipe = pipe->next;
	}
	return (NULL);
}

int		ensure_flow(t_lemin *node, t_room *r)
{
	t_pipe  *tmp;

	tmp = r->pipes;
	if (tmp->room->id == node->end->id)
		return (0);
	while (tmp)
	{
		if (tmp->flow < 0 && tmp->room->id != node->start->id)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}


int		get_residual(t_lemin *node, t_queue *q, t_parent *par)
{
	t_pipe *p;

	p = q->room->pipes;
	while (p)
	{
		if (p->room->visited >= node->v_token)
			p = p->next;
		else if (p->flow < 0 && p->room->id != node->start->id)
		{
			q_add(&q, p->room, par, p);
			p = p->next;
		}
		else
			p = p->next;
	}
	return (1);
}

int		q_offer(t_lemin *node, t_queue *q, t_parent *par)
{
	t_pipe *p;
	t_pipe *prev;

	p = q->room->pipes;
	prev = get_last(par, q->room);
	if (q->room->flag && q->room->id != node->start->id && prev && prev->flow == 0)
	{
		get_residual(node, q, par);
		return (0);
	}
	while (p)
	{
		if (p->flow > 0 || q_check(node, q, p->room))
			p = p->next;
		else if (p->room->visited >= node->v_token)
			p = p->next;
		else if (p->flow == 0 && p->room->flag)
		{
			if (!(ensure_flow(node, p->room)))
				q_add(&q, p->room, par, p);
			p = p->next;
		}
		else
		{
			q_add(&q, p->room, par, p);
			p = p->next;
		}
	}
	return (0);
}

int		calc_flow(t_room *where, t_room *to)
{
	t_pipe *tmp;

	tmp = where->pipes;
	while (tmp && tmp->room->id != to->id)
		tmp = tmp->next;
	tmp->flow += 1;
	tmp->adj->flow -= 1;
	return (0);
}

int		retrace_flow(t_lemin *node, t_parent *p)
{
	t_parent *tmp;
	t_room *r;

	node->antcount = node->antcount;
	if (!p)
		ft_error("retrace_flow: Cannot retrace!", NULL, 0);
	tmp = p;
	r = tmp->from;
	calc_flow(tmp->from, tmp->room);
	tmp->from->flag = 1;
	while (tmp->prev)
	{
		if (r->id == tmp->room->id)
		{
			r = tmp->from;
			r->flag = 1;
			calc_flow(r, tmp->room);
		}
		tmp = tmp->prev;
	}
	free_parent(node, &node->parent);
	return (1);
}

int		graph_flow(t_lemin *node, t_queue *q)
{
	t_parent *par;

	q_add(&q, node->start, NULL, NULL);
	par = init_parent(node, node->start);
	while (q)
	{
		if (q->room->id == node->end->id)
			break ;
		q_visit(node, q);
		q_offer(node, q, par);
		par = par->next;
		q = q_del(q);
	}
	if (!q)
	{
		free_parent(node, &node->parent);
		return (0);
	}
	q_free(&q);
	return (retrace_flow(node, par));
}

int		solve(t_lemin *node)
{
	int i;

	i = node->antcount;
	node->v_token = 1;
	node->m_token = 1;
	node->set_id = 1;
	while (i)
	{
		if (!(graph_flow(node, NULL)))
			break ;
		node->v_token += 1;
		new_set(&node->sets);
		graph_path(node, NULL, node->sets);
		gather_data(node, node->sets);
		node->m_token += 1;
		node->v_token += 1;
		i--;
	}
	calc(node, node->sets);
	choose_set(node, node->sets);
	print_inception(node, node->best);
	if (P_MOVES)
		ft_printf("lines: %d\n", node->steps);
	return (0);
}