/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathchooser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 01:20:58 by seronen           #+#    #+#             */
/*   Updated: 2020/10/19 15:53:47 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		calc_paths(t_map *map)
{
	t_pathf *p;

	p = map->paths;
	while (p)
	{
		map->max_moves += p->len;
		map->max_paths++;
		p = p->next;
	}
}

int		dispatch_ants(t_lemin *node, t_map *map)
{
	int *div;
	t_pathf *tmp;
	int i;

	map->calc = (map->max_moves + node->antcount) / map->max_paths;
	if (!map->ant)
		map->ant = (int*)malloc(sizeof(int) * map->max_paths + 1);
	i = 0;
	tmp = map->paths;
	while (tmp && i < map->max_paths)
	{
		if (map->ant[i] != -1)
			map->ant[i] = map->calc - tmp->len;
		else
			map->ant[i] = -1;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int		pathchooser(t_lemin *node, t_map *map)
{
	t_pathf *paths;
	int i;

	paths = map->paths;
	


	/*
	path_len(map->paths);
	calc_paths(map);
	if (!map->max_paths)
		ft_error("No paths found! : max_paths 0!");
	if (!paths)
		ft_error("No paths found! : !paths");
	dispatch_ants(node, map);
	i = 0;
	while (i < map->max_paths)
	{
		ft_printf("Path %d ants: %d\n", i + 1, map->ant[i]);
		i++;
	} */
	return (0);
}
