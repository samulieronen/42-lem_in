/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:26:59 by seronen           #+#    #+#             */
/*   Updated: 2020/10/29 22:37:36 by seronen          ###   ########.fr       */
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

int		q_offer(t_lemin *node, t_queue *q, t_parent *par)
{
	t_pipe *tmp;
	t_pipe *from;

	tmp = q->room->pipes;
	from = get_last(par, q->room);
	while (tmp && from && from->flow == 0)
	{
		if (tmp->flow < 0 && q->room->flag && tmp->room->id != node->start->id)
		{
			if (tmp->room->visited < node->v_token)
			{
				q_add(&q, tmp->room);
				q_parent(par, tmp);
			}
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = q->room->pipes;
	while (tmp)
	{
		if (tmp->flow > 0 || tmp->room->visited >= node->v_token || q_check(node, q, tmp->room))
			tmp = tmp->next;
		else
		{
			q_add(&q, tmp->room);
			q_parent(par, tmp);
			tmp = tmp->next;
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
		ft_error("retrace_flow: Cannot retrace, no parent!");
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
	free_parent(node, &node->parent); // Why intermittent segfault??
	return (1);
}

int		graph_flow(t_lemin *node, t_queue *q)
{
	t_parent *par;

	q_add(&q, node->start);
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
		free_parent(node, &node->parent); // Why intermittent segfault??
		return (0);
	}
	q_free(&q);
	return (retrace_flow(node, par));
}

int		solve(t_lemin *node)
{
	int i;
	t_set *head;

	i = node->antcount;
	node->v_token = 1;
	node->m_token = 1;
	while (i)
	{
		if (!(graph_flow(node, NULL)))
			break ;
		node->v_token += 1;
		new_set(&node->sets);
		graph_path(node, NULL, node->sets);
		calc(node, node->sets);
		node->m_token += 1;
		node->v_token += 1;
		i--;
	}
	int nb = 1;
	head = node->sets;
	while (head)
	{
		ft_printf("Set %d found\n", nb);
		int pnb = 0;
		t_pathf *p = head->paths;
		head->steps_total = 0;
		while (p)
		{
			ft_printf("Pathlen: %d\n", p->len);
			t_path *pp = p->path;
			while (pp)
			{
				ft_printf("%s ", pp->r->name);
				pp = pp->next;
			}
			ft_printf("\n");
			head->steps_total +=p->len;
			p = p->next;
			pnb++;
		}
		ft_printf("Paths in set: %d\n\n", pnb);
		head->amount = pnb;
		nb++;
		head = head->next;
	}
	return (0);
}