/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:50:36 by seronen           #+#    #+#             */
/*   Updated: 2020/10/21 01:52:53 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*get_modifier(t_lemin *node, t_room **r)
{
	if (node->mod == 1)
	{
		node->start = *r;
		return(ft_strdup("start"));
	}
	else if (node->mod == 2)
	{
		node->end = *r;
		return(ft_strdup("end"));
	}
	return (NULL);
}

t_room		*newroom(t_lemin *node, t_room **head)
{
	t_room *r;

	if (!(r = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	r->next = NULL;
	r->id = 0;
	r->name = NULL;
	r->pipes = NULL;
	r->info = NULL;
	r->visited = 0;
	if (*head)
	{
		r->next = *head;
		*head = r;
	}
	else
		*head = r;
	return (r);
}

int		build_room(t_lemin *node, char *line)
{
	t_room *r;

	r = newroom(node, &node->rooms);
	if (!r)
		ft_error("build_room: add_room failed!");
	r->id = ++node->roomnb;
	r->name = ft_strcdup(line, ' ');
	r->pipes = NULL;
	r->info = get_modifier(node , &r);
	node->mod = 0;
	r->visited = 0;
	insert_hash(node, r->name, r);
	return (0);
}
