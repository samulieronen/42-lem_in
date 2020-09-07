/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:37:03 by seronen           #+#    #+#             */
/*   Updated: 2020/09/07 23:45:44 by seronen          ###   ########.fr       */
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

t_room      *pathfinding(t_lemin *node, t_room *head, char *path) //set of paths //first set is ##start
{
	t_room *cur;
	t_room *next;
	t_pipe *pipes;

	if (!head)
		return (NULL);
	cur = head;
//	ft_printf("Current room: %s\n", cur->name);
	if (!cur->info)
		cur->visited = 1;
	pipes = cur->pipes;
	path = ft_strjoin(path, ft_strjoin("*", cur->name));
	if (cur->info && !ft_strcmp(cur->info, "end"))
	{
		ft_printf("FOUND A PATH: %s\n", path);
		return (NULL);
	}
	while (pipes)
	{
		if (!pipes)
			return (NULL);
//		ft_printf("Current room: %s\n", cur->name);
		while (!(next = fetch_room_path(node->rooms, ft_strdup(pipes->where))) && pipes->next)
			pipes = pipes->next;
		pathfinding(node, next, path);
//		ft_printf("In room: %s, pipe next.\n", cur->name);
		pipes = pipes->next;
	}
	cur->visited = 0;
	return (NULL);
}