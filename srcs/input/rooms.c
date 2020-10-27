/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:50:36 by seronen           #+#    #+#             */
/*   Updated: 2020/10/27 20:11:33 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*get_modifier(t_lemin *node, t_room *r)
{
	if (node->mod == 1)
	{
		ft_printf("Modid was start!\n");
		node->start = r;
		ft_printf("node->start->name: %s\n", node->start->name);
		node->mod = 0;
		return(ft_strdup("start"));
	}
	else if (node->mod == 2)
	{
		ft_printf("Modid was end!\n");
		node->end = r;
		ft_printf("node->end->name: %s\n", node->end->name);
		node->mod = 0;
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
	r->mapped = 0;
	r->flag = 0;
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

//	ft_printf("\n");
	r = newroom(node, &node->rooms);
	if (!r)
		ft_error("build_room: add_room failed!");
	r->id = 0;
	r->id = ++node->roomnb;
	r->name = ft_strcdup(line, ' ');
	r->pipes = NULL;
	r->info = NULL;
	r->visited = 0;
	r->mapped = 0;
	r->info = get_modifier(node , r);
	insert_hash(node, r->name, r);
//	ft_printf("%s\tHash inserted successfully!\n", r->name);
	return (0);
}
