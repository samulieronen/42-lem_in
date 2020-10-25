/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:26:59 by seronen           #+#    #+#             */
/*   Updated: 2020/10/25 15:47:36 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		q_visit(t_queue *q)
{
	t_queue *tmp;

	tmp = q;
	if (!q)
		return (1);
	if (tmp->room)
	{
		tmp->room->visited += 1;
//		ft_printf("Set %s to visited!\n", tmp->room->name);
		tmp = tmp->next;
	}
	else
		ft_error("Q_visit encountered an error!");
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

int		q_check(t_queue *q, t_room *r)
{
	t_queue *tmp;

	tmp = q;
	while (tmp)
	{
		if (tmp->room->id == r->id)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		q_offer(t_lemin *node, t_queue *q, t_pipe *p)
{
	if (p->flow > 0 || p->room->visited >= node->v_token || q_check(q, p->room))
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
//	ft_printf("Added parent %s from room %s\n", new->room->name, p->room->name);
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
	while (tmp->prev)
	{
		if (r->id == tmp->room->id)
		{
			r = tmp->from;
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

	q_add(&q, node->start);
	par = init_parent(node->start);
	head = par;
	while (q)
	{
		if (q->room->id == node->end->id)
			break ;
		q_visit(q);
		p = q->room->pipes;
		while (p)
		{
			if (q_offer(node, q, p))
			{
				q_add(&q, p->room);
				q_parent(par, p->room);
			}
			p = p->next;
		}
		par = par->next;
		q = q_del(q);
	}
	if (!q)
		return (0);
	return (retrace_flow(node, par));
}

int		solve(t_lemin *node)
{
	int i;

	i = node->antcount;
//	i = 1;
	node->v_token = 1;
	int *arr = (int*)malloc(sizeof(int) * node->roomnb + 1);
	int last = 0;
	int	nb = 1;
	while (i)
	{
		if (!(graph_flow(node, NULL)))
			break ;
		node->v_token += 1;
		ft_printf("Pathfinding\n");
		pathfinding(node, node->start, arr, 0);
/*		t_pathf *tmp;
		tmp = node->map->paths;
		int y = 0;
		while (tmp)
		{
			int k = 0;
			if (tmp->id_arr[0])
			{
				while (tmp->id_arr[k])
				{
					ft_printf("%d\t", tmp->id_arr[k]);
					k++;
				}
				tmp->id_arr[0] = 0;
				ft_printf("\n\n");
						y++;
			}
			tmp = tmp->next;
		}
		ft_printf("Paths in set %d: %d\n\n", nb, y);
		nb++; */
		node->v_token += 1;
		i--;
	}
	free(arr);
	return (0);
}