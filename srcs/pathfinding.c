/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:37:03 by seronen           #+#    #+#             */
/*   Updated: 2020/09/08 18:33:14 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*fetch_room_path(t_room *head, char *keyword)
{
	t_room *tmp;

	tmp = head;
	if (!head)
		ft_error("fetch_room failed, no matching rooms.");
	if (!ft_strcmp(keyword, "0"))
		return (NULL);
	while (tmp)
	{
		if ((!(ft_strcmp(tmp->name, keyword))) && !tmp->visited)
		{
			free(keyword);
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
	free(path);
	node->pathf = head;
}

t_room      *pathfinding(t_lemin *node, t_room *head, char *path) //set of paths //first set is ##start
{
	t_room *cur;
	t_room *next;
	t_pipe *pipes;

	if (!head)
		return (NULL);
	cur = head;
	if (!cur->info)
		cur->visited = 1;
	pipes = cur->pipes;
	if (!cur->info)
		path = ft_strjoin(path, ft_strjoin("*", cur->name));
	if (cur->info && !ft_strcmp(cur->info, "end"))
	{
//		ft_printf("FOUND A PATH: %s\n", path);
		add_path(node, path);
		return (NULL);
	}
	while (pipes)
	{
		if (!pipes)
			return (NULL);
		while (!(next = fetch_room_path(node->rooms, ft_strdup(pipes->where))) && pipes->next)
			pipes = pipes->next;
		pathfinding(node, next, path);
		pipes = pipes->next;
	}
	cur->visited = 0;
//	if (!cur->info)
//		free(path);
	return (NULL);
}