/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:40:24 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 23:59:37 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void        q_free(t_queue *head)
{
	t_queue *del;

	while (head->next)
	{
		del = head;
		head = head->next;
		free(del);
		del = NULL;
	}
	head = NULL;
}

t_queue		*q_del(t_queue *q)
{
	t_queue *del;

	if (!q || !q->next)
		return (NULL);
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
