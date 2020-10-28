/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:26:59 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 16:33:02 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		q_visit(t_lemin *node, t_queue *q)
{
	t_queue *tmp;

	tmp = q;
	if (!q)
		return (1);
//	while (tmp)
//	{
		if (tmp->room->id != node->end->id)
			tmp->room->visited = node->v_token;
//		tmp = tmp->next;
//	}
	return (0);
}

int		q_add(t_queue **q, t_room *new)
{
	t_queue *tmp;

	tmp = *q;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_queue*)malloc(sizeof(t_queue));
		tmp = tmp->next;
		tmp->room = new;
		tmp->next = NULL;
	}
	else
	{
		tmp = (t_queue*)malloc(sizeof(t_queue));
		tmp->room = new;
		tmp->next = NULL;
		*q = tmp;
	}
	return (0);
}

int		q_check(t_lemin *node, t_queue *q, t_room *r)
{
	t_queue *tmp;

	tmp = q;
	if (r->id == node->end->id)
		return (0);
	while (tmp)
	{
		if (tmp->room->id == r->id)
		{
//			ft_printf("\nRoom was already in queue!!!!\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_parent	*fetch_parent(t_parent *head, t_room *key)
{
	t_parent *p;

	p = head;
	while (p->prev)
	{
		if (p->room->id == key->id)
			return (p);
		p = p->prev;
	}
	return (NULL);
}

t_pipe		*get_last(t_lemin *node, t_parent *prev, t_room *to)
{
	t_parent 	*p;
	t_pipe		*pipe;

	if (!prev)
		return (NULL);
	p = fetch_parent(prev, to);
	if (!p)
		return (NULL);
//	ft_printf("parent: from %s to %s\n", p->from->name, p->room->name);
	pipe = p->from->pipes;
	while (pipe)
	{
		if (pipe->room->id == to->id)
			return (pipe);
		pipe = pipe->next;
	}
	return (NULL);
}

int		q_offer(t_lemin *node, t_queue *q, t_queue *head, t_parent *par)
{
	t_pipe *tmp;
	t_pipe *from;

	tmp = q->room->pipes;
	from = get_last(node, par, q->room);
//	ft_printf("in %s looking for options\n\n", q->room->name);
//	if (from)
//		ft_printf("from %s to %s\n", from->adj->room->name, from->room->name);
	while (tmp && from && from->flow == 0)
	{
		if (tmp->flow < 0 && tmp->room->flag && tmp->room->id != node->start->id)
		{
			if (tmp->room->visited < node->v_token)
			{
				q_add(&q, tmp->room);
				q_parent(par, tmp->room);
			}
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = q->room->pipes;
	while (tmp)
	{
		if (tmp->flow > 0 || tmp->room->visited >= node->v_token || q_check(node, head, tmp->room))
			tmp = tmp->next;
		else
		{
			q_add(&q, tmp->room);
			q_parent(par, tmp->room);
			tmp = tmp->next;
		}
	}
	return (0);
}

t_queue		*q_del(t_queue *q)
{
	t_queue *del;

	if (!q->next || !q)
		return (NULL);
	del = q->next;
	free(q);
	return (del);
}

t_parent	*parentnew(void)
{
	t_parent *new;

	new = (t_parent*)malloc(sizeof(t_parent));
	return (new);
}

t_parent	*init_parent(t_room *r)
{
	t_parent *p;

	p = (t_parent*)malloc(sizeof(t_parent));
	p->from = NULL;
	p->next = NULL;
	p->prev = NULL;
	p->room = r;
	return (p);
}

int		q_parent(t_parent *p, t_room *r)
{
	t_parent *new;
	t_parent *tmp;

	tmp = p;
	new = (t_parent*)malloc(sizeof(t_parent));
	new->room = r;
	new->from = p->room;
	while (tmp->next)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
	tmp->next->next = NULL;
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

	if (!p)
		return (0);
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
	return (1);
}

int		graph_flow(t_lemin *node, t_queue *q)
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
			break ;
		q_visit(node, q);
		q_offer(node, q, q_head, par);
		par = par->next;
		q = q->next;
	}
	if (!q)
		return (0);
	return (retrace_flow(node, par));
}

int		*new_set(t_set **alst)
{
	t_set *new;

	if (!(new = (t_set*)malloc(sizeof(t_set))))
		ft_error("new_set: Malloc failed!");
	new->paths = NULL;
	new->next = NULL;
	if (*alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	else if (new)
		*alst = new;
	return (0);
}

int		solve(t_lemin *node)
{
	int i;
	int flow;
	t_set *set;
	t_set *head;

	i = node->antcount;
	node->v_token = 1;
	node->m_token = 1;
	flow = 0;
	node->sets = NULL;
	while (i)
	{
		if (!(graph_flow(node, NULL)))
		{
			ft_printf("\ngraph_flow: no more possibilities\n");
			break ;
		}
		flow++;
		node->v_token += 1;
		new_set(&node->sets);
		graph_path(node, NULL, node->sets, &flow);
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
			head->steps_total +=p->len;
			p = p->next;
			pnb++;
		}
		ft_printf("Paths in set: %d\n\n", pnb);
		head->amount = pnb;
		nb++;
		head = head->next;
	}
	calc(node);
	return (0);
}