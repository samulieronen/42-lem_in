/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathchooser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:54:11 by seronen           #+#    #+#             */
/*   Updated: 2020/10/21 01:32:25 by seronen          ###   ########.fr       */
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
        break ;
    }
    return (0);
}

int		pathchooser2(t_lemin *node, t_map *map)
{
	t_pathf *paths;
	int i;

	if (!(paths = map->paths))
        ft_error("pathchooser: No paths found!");
    make_sets(node, paths);
    return (0);
}