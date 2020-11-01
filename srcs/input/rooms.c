/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:50:36 by seronen           #+#    #+#             */
/*   Updated: 2020/11/01 23:39:19 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char		*get_modifier(t_lemin *node, t_room *r)
{
	if (node->mod == 1)
	{
		node->start = r;
		node->mod = 0;
		return (ft_strdup("start"));
	}
	else if (node->mod == 2)
	{
		node->end = r;
		node->mod = 0;
		return (ft_strdup("end"));
	}
	return (NULL);
}

static void		init_room(t_room *r)
{
	r->next = NULL;
	r->id = 0;
	r->hash = 0;
	r->name = NULL;
	r->pipes = NULL;
	r->info = NULL;
	r->visited = 0;
	r->mapped = 0;
	r->flag = 0;
}

static t_room	*newroom(t_room **head)
{
	t_room *r;

	if (!(r = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	init_room(r);
	if (*head)
	{
		r->next = *head;
		*head = r;
	}
	else
		*head = r;
	return (r);
}

static char		*get_name(t_lemin *node, char *line)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (line[i] && line[i] != ' ' && ALLOW_SPACES)
		i++;
	if (line[0] == ' ' && !ALLOW_SPACES)
		ft_error("Spaces before data!", NULL, node->lnb);
	line[i] = '\0';
	return (line);
}

int				build_room(t_lemin *node, char *line)
{
	t_room	*r;
	char	*str;

	node->r_check = 1;
	if (node->l_check && !ALLOW_REORDER)
		ft_error("Input not in proper order!", NULL, node->lnb);
	validate_room(node, line);
	str = get_name(node, line);
	r = newroom(&node->rooms);
	if (!r)
		ft_error("build_room: add_room failed!", NULL, 0);
	r->id = ++node->roomnb;
	r->name = ft_strdup(str);
	r->info = get_modifier(node , r);
	insert_hash(node, r->name, r);
	return (0);
}
