/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:37:03 by seronen           #+#    #+#             */
/*   Updated: 2020/10/19 22:13:59 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			add_path(t_lemin *node, char *path)
{
	t_pathf *dest;
	t_pathf *head;

	if (CHOOSER)
		dest = node->map->paths;
	else
		dest = node->pathf;
	head = dest;
	if (!dest)
	{
		dest = (t_pathf*)malloc(sizeof(t_pathf));
		dest->next = NULL;
		head = dest;
	}
	else
	{
		while (dest->next)
			dest = dest->next;
		dest->next = (t_pathf*)malloc(sizeof(t_pathf));
		dest = dest->next;
		dest->next = NULL;
	}
	dest->path = ft_strdup(path);
	dest->len = 0;
//	free(path);
	if (CHOOSER)
		node->map->paths = head;
	else
		node->pathf = head;
}

int			check_next(t_lemin *node, t_pipe *pipe)
{
	t_room *room;

	room = pipe->room;
	if (room->visited)
		return (0);
	if (room->id == node->start->id)
		return (0);
	return (1);
}

t_room      *pathfinding(t_lemin *node, t_room *head, char *path)
{
	t_room *cur;
	t_pipe *pipes;

	if (!head)
		return (NULL);
	cur = head;
	pipes = cur->pipes;
	cur->visited = 1;
	if (!cur->info && !PATH_SAVE)
	{
		path = ft_strjoin(path, ft_strjoin("*", cur->name));
	}
	else if (cur->id != node->start->id && PATH_SAVE)
	{
		path = ft_strjoin(path, ft_strjoin("*", ft_itoa(cur->id)));
	}
	if (cur->id == node->end->id)
	{
		add_path(node, path);
		pipes = NULL;
	}
	while (pipes)
	{
		while (!check_next(node, pipes) && pipes->next)
			pipes = pipes->next;
		if (!check_next(node, pipes))
			break ;
		pathfinding(node, pipes->room, path);
		pipes = pipes->next;
	}
	cur->visited = 0;
	return (NULL);
}
