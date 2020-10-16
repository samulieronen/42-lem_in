/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:37:03 by seronen           #+#    #+#             */
/*   Updated: 2020/10/17 00:19:03 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*fetch_modroom(t_room *head, char *keyword)
{
	t_room *tmp;

	tmp = head;
	if (!head)
		ft_error("fetch_room failed, no matching rooms.");
	while (tmp)
	{
		if (tmp->info)
		{
			if (!(ft_strcmp(tmp->info, keyword)))
				return (tmp); 
		}
		tmp = tmp->next;
	}
	return (NULL);
}

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
	free(path);
	if (CHOOSER)
		node->map->paths = head;
	else
		node->pathf = head;
}

int			check_next(t_pipe *pipe)
{
	t_room *room;

	room = pipe->room;
	if (room->visited)
		return (0);
	if (room->info && !ft_strcmp(room->info, "start"))
		return (0);
	return (1);
}

t_room      *pathfinding(t_lemin *node, t_room *head, char *path) //set of paths //first set is ##start
{
	t_room *cur;
	t_pipe *pipes;
	char *tmp;
	char *ttmp;

	if (!head)
		return (NULL);
	cur = head;
	if (!cur->info)
		cur->visited = 1;
	if (!cur->info)
		path = ft_strjoin(path, ft_strjoin("*", cur->name));
	if (cur->info && !ft_strcmp(cur->info, "end"))
	{
		add_path(node, path);
		return (NULL);
	}
	pipes = cur->pipes;
	while (pipes)
	{
		if (!pipes)
			break ;
		while (!check_next(pipes) && pipes->next)
			pipes = pipes->next;
		if (!check_next(pipes))
			break ;
		pathfinding(node, pipes->room, path);
		pipes = pipes->next;
	}
	cur->visited = 0;
	return (NULL);
}