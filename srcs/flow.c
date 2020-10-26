/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:26:59 by seronen           #+#    #+#             */
/*   Updated: 2020/10/26 19:40:36 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		q_visit(t_lemin *node, t_queue *q)
{
	t_queue *tmp;

	tmp = q;
	if (!q)
		return (1);
	while (tmp)
	{
		if (tmp->room->id != node->end->id)
			tmp->room->visited = node->v_token;
		tmp = tmp->next;
	}
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
//		ft_printf("'%s' ", tmp->room->name);
		if (tmp->room->id == r->id)
		{
			ft_printf("\nRoom was already in queue!!!!\n");
			return (1);
		}
		tmp = tmp->next;
	}
//	ft_printf("\n");
	return (0);
}

int		q_offer(t_lemin *node, t_queue *q, t_queue *head, t_parent *par)
{
	t_pipe *tmp;

	tmp = q->room->pipes;
	while (tmp)
	{
		if (tmp->flow < 0 && tmp->room->id != node->start->id && tmp->room->visited < node->v_token)
		{
			if (tmp->room->visited < node->v_token)
			{
//				printf("Here1\n");
				q_add(&q, tmp->room);
//				ft_printf("room %s added\n", tmp->room->name);
				q_parent(par, tmp->room);
//				*par = (*par)->next;
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
//			printf("Here2\n");
			q_add(&q, tmp->room);
			q_parent(par, tmp->room);
			tmp = tmp->next;
//			*par = (*par)->next;
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
//		printf("%p\n", par);
		q_offer(node, q, q_head, par);
		par = par->next;
		q = q->next;
//		q = q_del(q);
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
	ft_bzero(arr, node->roomnb);
	int last = 0;
	int	nb = 1;
	i = 3;
	while (i)
	{
		if (!(graph_flow(node, NULL)))
		{
			ft_printf("\ngraph_flow: no more possibilities\n");
			break ;
		}
		node->v_token += 1;
		graph_path(node, NULL);
		ft_printf("\n\n");
		node->v_token += 1;
		i--;
	}
	free(arr);
	return (0);
}