/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathchooser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:54:11 by seronen           #+#    #+#             */
/*   Updated: 2020/10/22 21:57:29 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int a_iter = 0;
int b_iter = 0;
int comp_call = 0;
size_t comp_iters = 0;

int		compare(t_lemin *node, int **a, int **b)
{
	int i;
	int k;
	int j;

	if (!a || !b)
		ft_error("compare paths: (a || b) == NULL!");
	comp_call++;
	i = 0;
	while (a[i])
	{
		k = 0;
		while (a[i][k])
		{
			j = 0;
			while (b[0][j])
			{
				if (a[i][k] == b[0][j] && (a[i][k] != node->start->id && a[i][k] != node->end->id))
					return (1);
				comp_iters++;
				j++;
			}
			k++;
		}
		i++;
	}
	return (0);
}

int		compare_sets(t_lemin *node, t_set *s)
{
	t_set *at;
	t_set *bt;

	at = s;
	while (at)
	{
		bt = s;
		while (bt)
		{
			if (!(compare(node, at->setarr, bt->setarr)))
				b_iter = b_iter;
//				ft_printf("Diff path found!\n");
			b_iter++;
			bt = bt->next;
		}
		a_iter++;
		at = at->next;
	}
	return (0);
}

int		pathchooser2(t_lemin *node, t_map *map)
{
	t_pathf *paths;
	int i;

	if (!(paths = map->paths))
		ft_error("pathchooser: No paths found!");
	manage_sets(node, paths);
	compare_sets(node, node->map->sets);
	ft_printf("OK ITERS DONE == iters: comp_call = %d, a = %d, b = %d, tot = %d, COMP: %zu\n\n", comp_call, a_iter, b_iter, a_iter * b_iter, comp_iters);
	return (0);
}