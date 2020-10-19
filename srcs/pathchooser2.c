/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathchooser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:54:11 by seronen           #+#    #+#             */
/*   Updated: 2020/10/19 22:18:13 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"



int     make_sets(t_lemin *node, t_pathf *paths)
{
    t_pathf *tmp;
    t_set   *sets;

    tmp = paths;
    while (tmp)
    {
        
    }
    return (0);
}

int		pathchooser2(t_lemin *node, t_map *map)
{
	t_pathf *paths;
	int i;

	paths = map->paths;
    make_sets(node, paths);
    return (0);
}