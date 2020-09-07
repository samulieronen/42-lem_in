/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:59:12 by seronen           #+#    #+#             */
/*   Updated: 2020/09/08 00:07:59 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     ant_count(t_lemin *node)
{
	char *line;

	get_next_line(0, &line);
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
		node->log->modid = 1;
	else if (!(ft_strcmp("##end", line)))
		node->log->modid = 2;
	else
		ft_error("Invalid modifier!");
	return (0);
}

void	add_room(t_lemin *node, char *id, char *info)
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
	dest->name = id;
	dest->pipes = NULL;
	dest->info = info;
	dest->visited = 0;
	dest->dead = 0;
	dest->paths_used = 0;
	node->rooms = head;
}

t_room	*fetch_room(t_room *head, char *keyword)
{
	t_room *tmp;

	tmp = head;
	if (!head)
		ft_error("fetch_room failed, no matching rooms.");
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, keyword)))
		{
			free(keyword);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_pipe(t_room *room, char *where)
{
	t_pipe *dest;
	t_pipe *head;

	dest = room->pipes;
	head = room->pipes;
	if (!dest)
	{
		dest = (t_pipe*)malloc(sizeof(t_pipe));
		dest->next = NULL;
		head = dest;
	}
	else
	{
		while (dest->next)
			dest = dest->next;
		dest->next = (t_pipe*)malloc(sizeof(t_pipe));
		dest = dest->next;
		dest->next = NULL;
	}
	dest->where = ft_strdup(where);
	dest->dead = 0;
	room->pipes = head;
}

int		check_pipes(t_pipe *head, char *name)
{
	t_pipe *tmp;

	tmp = head;
	if (!head)
		return (0);
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->where, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		build_pipes(t_lemin *node, char *line, int rev)
{
	t_room *room;
	t_pipe *pipe;
	int i;

	i = 0;
	if (!(room = fetch_room(node->rooms, ft_strcdup(line, '-'))))
		ft_error("Fetch room failed, cannot find room.");
	pipe = room->pipes;
	while (line[i] && line[i] != '-')
		i++;
	if (!check_pipes(room->pipes, &line[i + 1]))
	{
		add_pipe(room, &line[i + 1]);
	}
	if (!rev)
		build_pipes(node, ft_strrev(line), 1);
	else
		free(line);
	return (0);
}

int		build_room(t_lemin *node, char *line)
{
	if (node->log->modid == 1)
	{
		add_room(node, ft_strcdup(line, ' '), ft_strdup("start"));
	}
	else if (node->log->modid == 2)
	{
		add_room(node, ft_strcdup(line, ' '), ft_strdup("end"));
	}
	else
		add_room(node, ft_strcdup(line, ' '), NULL);
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
	while (get_next_line(0, &line))
	{
		if (!line)
			break ;
		ft_printf("%s\n", line);
		parse_line(node, line);
		if (line)
			ft_strdel(&line);
	}
	ft_printf("\n\n");
/*	while (node->rooms)
	{
		printf("Found room %s\n", node->rooms->name);
		if (node->rooms->info)
			printf("%s\n", node->rooms->info);
		while (node->rooms->pipes)
		{
			printf("Pipe to '%s'\n", node->rooms->pipes->where);
			node->rooms->pipes = node->rooms->pipes->next;
		}
		printf("\n");
		node->rooms = node->rooms->next;
	}
	ft_printf("\n\n"); */
	return (0);
}