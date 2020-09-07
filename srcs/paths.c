/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 16:01:50 by seronen           #+#    #+#             */
/*   Updated: 2020/09/07 19:45:35 by seronen          ###   ########.fr       */
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

char	*check_visited(t_lemin *node, char *roomkey)
{
	t_room *room;

	room = fetch_room(node->rooms, ft_strdup(roomkey));
	if (room->visited || room->dead)
	{
//		ft_printf("Validate_next: room '%s' dead or visited\n", room->name);
		return (NULL);
	}
	return (roomkey);
}

char    *validate_next(t_lemin *node, t_room *room)
{
	t_pipe *tmp;
	t_room *next;

	tmp = room->pipes;
	while (tmp)
	{
		if (!room->dead && ft_strcmp(tmp->where, "0"))
		{
			if (check_visited(node, tmp->where))
				return (tmp->where);
		}
		tmp = tmp->next;
	}
	room->dead = 1;
	return (NULL);
}

void		clear_visited(t_lemin *node)
{
	t_room *tmp;

	tmp = node->rooms;
	while (tmp)
	{
		if (tmp->visited == 1)
			tmp->visited = 0;
		tmp = tmp->next;
	}
}

void	exclude_path(t_lemin *node, char *path)
{
	int i;
	int nb;
	t_room *room;
	t_pipe *tmp;

	i = 2;
	while (path[i] && (i < (int)ft_strlen(path) - 2))
	{
		nb = 0;
		room = fetch_room(node->rooms, ft_strcdup(&path[i], '*'));
		tmp = room->pipes;
		while (tmp)
		{
			tmp = tmp->next;
			nb++;
		}
		room->paths_used += 1;
//		ft_printf("Paths used for room '%s': %d -- %d\n", room->name, room->paths_used, nb - 1);
		if (room->paths_used == nb - 1)
		{
			ft_printf("Room '%s' visited set to 2: %d -- %d\n", room->name, room->paths_used, nb - 1);
			room->visited = 2;
		}
		i += 2;
	}
}

char     *get_paths(t_lemin *node)
{
	t_room *room;
	t_room *newroom;
	t_pipe *pipes;
	char *path;
	char *roomkey;

	room = fetch_modroom(node->rooms, "start");
	pipes = room->pipes;
	path = ft_strjoin(room->name, "*");
	if (!(validate_next(node, room)))
	{
		ft_printf("OK that's it then\n");
		return (NULL);
	}
	while (1)
	{
		if ((roomkey = validate_next(node, room)) != NULL)
		{
//			ft_printf("Room '%s'\n", room->name);
			newroom = fetch_room(node->rooms, ft_strdup(roomkey));
			if (!room->info)
				room->visited = 1;
			room = newroom;
//			ft_printf("Newroom '%s'\n", room->name);
			pipes = room->pipes;
			path = ft_strjoin(path, ft_strjoin(room->name, "*"));
			if (room->info && !ft_strcmp(room->info, "end"))
			{
				ft_printf("FOUND A PATH!\n");
				printf("The path: %s\n", path);
				exclude_path(node, path);
				clear_visited(node);
				get_paths(node);
				return (NULL);
			}
		}
		else
		{
//			ft_printf("Recursion time\n");
			free(path);
			clear_visited(node);
			get_paths(node);
			return (NULL);
		}
	}
	ft_printf("SHEESH! GET REKT!\n");
	return (NULL);
}
