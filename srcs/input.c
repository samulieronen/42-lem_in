/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:59:12 by seronen           #+#    #+#             */
/*   Updated: 2020/10/19 20:32:16 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     ant_count(t_lemin *node)
{
	char *line;

	if (get_next_line(0, &line) < 0)
		ft_error("Invalid file");
	node->antcount = ft_atoi(line);
	if (node->antcount < 1 || node->antcount > INT32_MAX)
		ft_error("Number of ants impossible!");
	ft_printf("%s\n", line);
	ft_strdel(&line);
	return (0);
}

int     get_modifier(t_lemin *node, char *line)
{
	if (!(ft_strcmp("##start", line)))
	{
		node->log->modid = 1;
	}
	else if (!(ft_strcmp("##end", line)))
	{
		node->log->modid = 2;
	}
	return (0);
}

t_room		*add_room(t_lemin *node, char *id, char *info)
{
	t_room *dest;
	t_room *head;

	dest = node->rooms;
	head = node->rooms;
	if (!dest)
	{
		dest = (t_room*)malloc(sizeof(t_room));
		dest->next = NULL;
		head = dest;
	}
	else
	{
		while (dest->next)
			dest = dest->next;
		dest->next = (t_room*)malloc(sizeof(t_room));
		dest = dest->next;
		dest->next = NULL;
	}
	dest->id = ++node->roomnb;
	dest->name = id;
	dest->pipes = NULL;
	dest->info = info;
	dest->visited = 0;
	node->rooms = head;
	return (dest);
}

t_room	*fetch_room(t_room *head, char *keyword)
{
	t_room *tmp;

	tmp = head;
//	ft_printf("key: %s\n", keyword);
	if (!head)
		ft_error("fetch_room failed, no rooms.");
	while (tmp)
	{
//		ft_printf("name: %s\n", tmp->name);
		if (!(ft_strcmp(tmp->name, keyword)))
		{
			free(keyword);
			return (tmp);
		}
		tmp = tmp->next;
	}
	ft_error("fetch_room failed, cannot find room.");
	return (NULL);
}

int		add_pipe(t_room *room, t_room *where)
{
	t_pipe *dest;
	t_pipe *head;

	dest = room->pipes;
	head = room->pipes;
	if (!dest)
	{
		if (!(dest = (t_pipe*)malloc(sizeof(t_pipe))))
			ft_error("add_pipe: Malloc failed!");
		head = dest;
	}
	else
	{
		while (dest->next)
			dest = dest->next;
		if (!(dest->next = (t_pipe*)malloc(sizeof(t_pipe))))
			ft_error("add_pipe: Malloc failed!");
		dest = dest->next;
		dest->next = NULL;
	}
	dest->room = where;
	dest->next = NULL;
	room->pipes = head;
	return (0);
}

int		build_pipes(t_lemin *node, char *line, int rev)
{
	t_room *room;
	t_room *where;
	t_pipe *pipe;
	int i;

	i = 0;
	if (!(room = fetch_room(node->rooms, ft_strcdup(line, '-'))))
		ft_error("Fetch room failed, cannot find room.");
	pipe = room->pipes;
	while (line[i] && line[i] != '-')
		i++;
	if (!(where = fetch_room(node->rooms, ft_strcdup(&line[i + 1], '-'))))
		ft_error("Fetch room failed, cannot find room.");
	add_pipe(room, where);
	add_pipe(where, room);
	return (0);
}

int		build_room(t_lemin *node, char *line)
{
	if (node->log->modid == 1)
	{
		node->start = add_room(node, ft_strcdup(line, ' '), ft_strdup("start"));
	}
	else if (node->log->modid == 2)
	{
		node->end =  add_room(node, ft_strcdup(line, ' '), ft_strdup("end"));
	}
	else
	{
		add_room(node, ft_strcdup(line, ' '), NULL);
	}
	node->log->modid = 0;
	return (0);
}

int     parse_line(t_lemin *node, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strstr(line, "##"))
	{
		get_modifier(node, line);
	}
	else if (line[i] == '#' && line[i + 1] != '#')
	{
		return (0);
	}
	else if (ft_strchr(line, '-'))
	{
		build_pipes(node, line, 0);
	}
	else
	{
		build_room(node, line);
	}
	return (0);
}

int     get_input(t_lemin *node)
{
	char    *line;

	ant_count(node);
	while (get_next_line(0, &line) > 0)
	{
		if (!line)
			break ;
		if (PRINT_IN)
			ft_printf("%s\n", line);
		if (parse_line(node, line))
			ft_error("Parse line failed!");
		if (line)
			ft_strdel(&line);
	}
	ft_printf("\n\n");
	return (0);
}