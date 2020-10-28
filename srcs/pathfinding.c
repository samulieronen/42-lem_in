/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:37:03 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 14:07:41 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				*pathdup(int *old)
{
	int i;
	int len;
	int *new;

	i = 0;
	len = 0;
	while (old[len])
	{
		len++;
	}
	new = (int*)malloc(sizeof(int) * len);
	ft_bzero(new, len);
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

t_pathf			*pathnew(int *p, int len)
{
	t_pathf *new;

	if (!(new = (t_pathf*)malloc(sizeof(t_pathf))))
		ft_error("pathnew: Malloc failed!");
	new->id_arr = pathdup(p);
	new->len = len;
	new->next = NULL;
	return (new);
}

void			add_path(t_pathf **alst, t_pipe **p, int *path, int len)
{
	t_pathf *new;

	new = pathnew(path, len);
	if (*alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	else if (new)
		*alst = new;
}

int			check_next(t_lemin *node, t_pipe *pipe)
{
	t_room *room;

	room = pipe->room;
	if (room->visited >= node->v_token || room->id == node->start->id)
		return (0);
	if (room->visited < node->v_token)
	{
		return (1);
	}
	return (0);
}

int      pathfinding(t_lemin *node, t_room *head, int *p, int len)
{
	t_room *cur;
	t_pipe *pipes;

	if (!head)
		return (0);
	cur = head;
	pipes = cur->pipes;
	if (cur->id != node->end->id)
		cur->visited = node->v_token;
	p[len] = cur->id;
	if (cur->id == node->end->id)
	{
		p[len + 1] = 0;
		add_path(&node->map->paths, &pipes, p, len);
		pipes = NULL;
	}
	while (pipes)
	{
		while (pipes && (!check_next(node, pipes)))
			pipes = pipes->next;
		if (!pipes)
			break ;
		pathfinding(node, pipes->room, p, len + 1);
		pipes = pipes->next;
	}
	p[len] = 0;
	cur->visited = 0;
	return (0);
}
