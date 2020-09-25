/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathchoosing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 18:16:24 by seronen           #+#    #+#             */
/*   Updated: 2020/09/17 02:51:26 by seronen          ###   ########.fr       */
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
			if (ft_isdigit(tmp->path[i]))
				tmp->len++;
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int		math_movecount(t_lemin *node, t_pathf *path)
{
	int ants;
	int mv;

	ants = node->antcount;
	mv = (path->len + ants) - 1;
	return (mv);
}

int		math_movecount2(t_lemin *node, int *list)
{
	int ants;
	int mv;
	int i;

	ants = node->antcount;
	return (0);
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
	dest->path = NULL;
	node->sets = head;
	return (dest);
}

int		add_to_set(t_pathset *set, t_pathf *path)
{
	t_pathf *tmp;

	if (!path || !set)
		return (1);
	tmp = set->path;
	if (!set->path)
	{
		set->path = path;
		set->path->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = path;
		tmp->next->next = NULL;
	}
	return (0);
}

int		sort_intersecting(t_lemin *node, t_pathf *paths, int max_paths)
{
	t_pathf		*tmp;
	t_pathf		*cur;
	t_pathset	*set;
	int 	nb;

	cur = paths;
	while (cur)
	{
		nb = 1;
		ft_printf("The path: %s\n",cur->path);
		tmp = paths;
		set = add_pathset(node);
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
					ft_printf("Not intersecting with: %s\n",tmp->path);
				}
			}
			tmp = tmp->next;
		}
		set->pathset = (max_paths - nb) + 1;
		ft_printf("Pathsetlen: %d\n", set->pathsetlen);
		ft_printf("Paths to use: %d\n\n", set->pathset);
		cur = cur->next;
	}
	return (0);
}

/*
** We calculate the optimal amount of ants we send per path:
** (total amount of steps of all paths + total number of ants) / number ofjj	// Huge thanks to gmolin! :) Luv u
** paths - steps in current path.
*/

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
	ft_printf("Checking intersections : max_paths %d\n\n", max_paths);
	sort_intersecting(node, paths, max_paths);
	int res;
	if (10 % 3 != 0)
		ft_printf("There will be a remainder to sort out!\n");
	res = (12 + 10) / 3;
	ft_printf("%d\n\n", res - 4);
	ft_printf("%d\n\n", res - 6);
	ft_printf("%d\n\n", res - 2);
	return (0);
}
