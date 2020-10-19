/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathchoosing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 18:16:24 by seronen           #+#    #+#             */
/*   Updated: 2020/10/19 18:44:35 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		path_len(t_pathf *head)
{
	t_pathf *tmp;
	int i;

	tmp = head;
	while (tmp)
	{
		i = 0;
		tmp->len = 1;
		while (tmp->path[i])
		{
			if (tmp->path[i] == '*')
				tmp->len++;
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int		math_movecount(t_lemin *node, t_pathf *path)
{
	return ((path->len + node->antcount) - 1);
}

int		check_intersecting(char *p1, char *p2)
{
	int i;
	char *needle;

	i = 0;
	while (p1[i])
	{
		i++;
		needle = ft_strcdup(&p1[i], '*');
		if (ft_strstr(p2, needle))
			return (1);
		while (p1[i] && p1[i] != '*')
			i++;
	}
	return (0);
}

t_pathset			*add_pathset(t_lemin *node)
{
	t_pathset *dest;
	t_pathset *head;

	dest = node->sets;
	head = dest;
	if (!dest)
	{
		dest = (t_pathset*)malloc(sizeof(t_pathset));
		dest->next = NULL;
		head = dest;
	}
	else
	{
		while (dest->next)
			dest = dest->next;
		dest->next = (t_pathset*)malloc(sizeof(t_pathset));
		dest = dest->next;
		dest->next = NULL;
	}
	dest->pathset = 0;
	dest->pathsetlen = 0;
	dest->movetable = NULL;
	dest->anttable = NULL;
	dest->path = NULL;
	node->sets = head;
	return (dest);
}

t_pathf *dup_path(t_pathf *old)
{
	t_pathf *new;

	new = (t_pathf*)malloc(sizeof(t_pathf));
	new->path = old->path;
	new->len = old->len;
	return (new);
}

int		add_to_set(t_pathset *set, t_pathf *path)
{
	t_pathf *tmp;

	if (!path || !set)
		return (1);
	tmp = set->path;
	if (!set->path)
	{
		set->path = dup_path(path);
		set->path->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = dup_path(path);
		tmp->next->next = NULL;
	}
	return (0);
}

int		add_shortest_set(t_lemin *node)
{
	t_pathf *tmp;
	t_pathf *min;

	tmp = node->pathf;
	min = tmp;
	while (tmp)
	{
		if (tmp->len < min->len)
			min = tmp;
		tmp = tmp->next;
	}
	node->sets = add_pathset(node);
	if (add_to_set(node->sets, min))
		ft_error("Internal error: could not add path to set!");
	node->sets->pathsetlen += min->len;
	node->sets->pathset = 1;
	return (0);
}

int		sort_intersecting(t_lemin *node, t_pathf *paths, int max_paths)
{
	t_pathf		*tmp;
	t_pathf		*cur;
	t_pathset	*set;
	int 		nb;

	cur = paths;
	add_shortest_set(node);
	while (cur)
	{
		nb = 1;
//		ft_printf("The path: %s\n",cur->path);
		tmp = paths;
		set = add_pathset(node);
		if (add_to_set(set, cur))
			ft_error("Internal error: could not add path to set!");
		set->pathsetlen += cur->len;
		while (tmp)
		{
			if (ft_strcmp(tmp->path, cur->path))
			{
				if (check_intersecting(cur->path, tmp->path))
					nb++;
				else
				{
					set->pathsetlen += tmp->len;
					if (add_to_set(set, tmp))
						ft_error("Internal error: could not add path to set!");
//					ft_printf("Not intersecting with: %s\n",tmp->path);
				}
			}
			tmp = tmp->next;
		}
		set->pathset = (max_paths - nb) + 1;
//		ft_printf("Pathsetlen: %d\n", set->pathsetlen);
//		ft_printf("Paths to use: %d\n\n", set->pathset);
		cur = cur->next;
	}
	return (0);
}

/*
** We calculate the optimal amount of ants we send per path:
** (total amount of steps of all paths + total number of ants) / number ofjj	// Huge thanks to gmolin! :) Luv u
** paths - steps in current path.
*/

int		sort_ants(t_lemin *node, t_pathset *sets)
{
	t_pathset	*set;
	t_pathf		*path;
	int			res;
	int			i;
	int			calc;

	set = sets;
	while (set)
	{
		path = set->path;
		res = 0;
		calc = (set->pathsetlen + node->antcount) / set->pathset;
		set->anttable = (int*)malloc(sizeof(set->pathset) + 1);
		i = 0;
		while (path)
		{
			res = (calc - path->len);
			set->anttable[i++] = res;
			path = path->next;
		}
		if (node->antcount % set->pathset != 0)
//			ft_printf("Remainder to be sorted out!\n");
		set = set->next;
	}
//	check_remainder();
	return (0);
}

// Moves are antcount in path + path length - 1.

t_pathset		*get_best(t_pathset *sets)
{
	t_pathset	*tmp;
	t_pathset	*best;

	tmp = sets;
	best = tmp;
	while (tmp)
	{
//		ft_printf("Moves: %d\n", tmp->moves);
		if (tmp->moves <= best->moves)
			best = tmp;
		tmp = tmp->next;
	}
	return (best);
}

int				get_maxmoves(int *arr)
{
	int i;
	int max;

	i = 0;
	max = arr[0];
	while (arr[i])
	{
		if (arr[i] > max)
			max = arr[i];
		i++;
	}
	return (max);
}

t_pathset		*calc_moves(t_lemin *node, t_pathset *sets)
{
	t_pathset	*cur;
	t_pathf		*tmp;
	int i;

	cur = sets;
	while (cur)
	{
		i = 0;
		cur->movetable = (int*)malloc(sizeof(int) * cur->pathset) + 1;
		tmp = cur->path;
		while (tmp)
		{
			cur->movetable[i] = (cur->anttable[i] + tmp->len) - 1;
			i++;
			tmp = tmp->next;
		}
		cur->moves = get_maxmoves(cur->movetable);
		cur = cur->next;
	}
	return (get_best(sets));
}

int		pathchoosing(t_lemin *node)
{
	t_pathf *paths;
	t_pathf *tmp;
	t_pathf *ttmp;

	paths = node->pathf;
	if (!paths)
		ft_error("No paths found!");
	path_len(paths);
	int max_paths = 0;
	ttmp = paths;
	while (ttmp)
	{
		max_paths++;
		math_movecount(node, ttmp);
		ttmp = ttmp->next;
	}
//	ft_printf("Checking intersections : max_paths %d\n\n", max_paths);
	sort_intersecting(node, paths, max_paths);
	sort_ants(node, node->sets);
	t_pathset *use;
	use = calc_moves(node, node->sets);
	ft_printf("\n\n\n\nPathset to_use found!\n\n");
	int i = 0;
	while (use->path)
	{
//		ft_printf("Path: %s\nAnts: %d\nMoves: %d\n\n", use->path->path, use->anttable[i], use->movetable[i]);
		i++;
		use->path = use->path->next;
	}
	ft_printf("Movecount: %d\n\n", use->moves);
//	ft_printf("Path with 100 steps : %d\n", ses - 100);
	return (0);
}
