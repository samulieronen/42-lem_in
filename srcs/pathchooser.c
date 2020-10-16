/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathchooser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 01:20:58 by seronen           #+#    #+#             */
/*   Updated: 2020/10/17 00:21:44 by seronen          ###   ########.fr       */
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

	map->ant = (int*)malloc(sizeof(int) * map->max_paths + 1);
	map->path = (int*)malloc(sizeof(int) * map->max_paths + 1);
	i = 0;
	while (tmp)
	{
		map->ant[i] = 0;
		i++;
	}
	return (0);
}



int		pathchooser(t_lemin *node, t_map *map)
{
	t_pathf *paths;

	paths = map->paths;
	calc_paths(map);
	if (!map->max_paths)
		ft_error("No paths found! : max_paths 0!");
	if (!paths)
		ft_error("No paths found! : !paths");
//	dispatch_ants();
	return (0);
}
