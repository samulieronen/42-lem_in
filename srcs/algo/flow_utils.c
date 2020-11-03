/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:36:52 by seronen           #+#    #+#             */
/*   Updated: 2020/11/03 13:05:51 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pipe		*get_last(t_parent *prev, t_room *to)
{
	t_parent	*p;
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

int			ensure_flow(t_lemin *node, t_room *r)
{
	t_pipe	*tmp;

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

int			calc_flow(t_room *where, t_room *to)
{
	t_pipe *tmp;

	tmp = where->pipes;
	while (tmp && tmp->room->id != to->id)
		tmp = tmp->next;
	tmp->flow += 1;
	tmp->adj->flow -= 1;
	return (0);
}

int			get_residual(t_lemin *n, t_queue *q, t_parent *p, t_pipe *pr)
{
	t_pipe *pipes;

	if (!q->room->flag || q->room->id == n->start->id)
		return (0);
	if (!pr || pr->flow != 0)
		return (0);
	pipes = q->room->pipes;
	while (pipes)
	{
		if (pipes->room->visited >= n->v_token)
			pipes = pipes->next;
		else if (pipes->flow < 0 && pipes->room->id != n->start->id)
		{
			q_add(&q, pipes->room, p, pipes);
			pipes = pipes->next;
		}
		else
			pipes = pipes->next;
	}
	return (1);
}
