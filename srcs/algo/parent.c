/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:01:21 by seronen           #+#    #+#             */
/*   Updated: 2020/10/29 22:04:32 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_parent	*parentnew(void)
{
	t_parent *new;

	new = (t_parent*)malloc(sizeof(t_parent));
	return (new);
}

t_parent	*init_parent(t_lemin *node, t_room *r)
{
	t_parent *p;

	p = (t_parent*)malloc(sizeof(t_parent));
	p->from = NULL;
	p->next = NULL;
	p->prev = NULL;
	p->room = r;
	node->parent = p;
	return (p);
}

int		q_parent(t_parent *p, t_pipe *pipe)
{
	t_parent *new;
	t_parent *tmp;

	tmp = p;
	new = (t_parent*)malloc(sizeof(t_parent));
	new->room = pipe->room;
//	new->edge = pipe;
	new->from = p->room;
	while (tmp->next)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
	tmp->next->next = NULL;
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

void		free_parent(t_lemin *node, t_parent **alst)
{
	t_parent *temp;
	t_parent *tempnext;

	temp = *alst;
	while (temp)
	{
		tempnext = temp->next;
		free(temp);
		temp = tempnext;
	}
	*alst = NULL;
	node->parent = NULL;
}
