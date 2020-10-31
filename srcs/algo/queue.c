/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:40:24 by seronen           #+#    #+#             */
/*   Updated: 2020/10/31 21:53:02 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void        q_free(t_queue **alst)
{
	t_queue *temp;
	t_queue *tempnext;

	temp = *alst;
	if (!alst)
		return ;
	while (temp)
	{
		tempnext = temp->next;
		free(temp);
		temp = tempnext;
	}
	*alst = NULL;
}

t_queue		*q_del(t_queue *q)
{
	t_queue *del;

	if (!q)
		return (NULL);
	if (!q->next)
	{
		free(q);
		return (NULL);
	}
	del = q->next;
	free(q);
	return (del);
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
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		q_add(t_queue **q, t_room *new, t_parent *par, t_pipe *p)
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
	if (par && p)
		q_parent(par, p);
	return (0);
}

int		q_visit(t_lemin *node, t_queue *q)
{
	t_queue *tmp;

	tmp = q;
	if (!q)
		return (1);
	if (tmp->room->id != node->end->id)
		tmp->room->visited = node->v_token;
	return (0);
}

int		q_unvisit(t_lemin *node, t_queue *q)
{
	t_queue *tmp;

	tmp = q;
	if (!q)
		return (1);
	if (tmp->room->id != node->end->id)
		tmp->room->visited -= 1;
	return (0);
}