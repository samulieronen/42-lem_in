/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathchoosing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 18:16:24 by seronen           #+#    #+#             */
/*   Updated: 2020/09/08 19:10:29 by seronen          ###   ########.fr       */
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

	ants = node->antcount;
	printf("Movecount: %d\n", path->len + ants - 1);
	return (0);
}

int		pathchoosing(t_lemin *node)
{
	t_pathf *paths;

	paths = node->pathf;
	path_len(paths);
	while (paths)
	{
		math_movecount(node, paths);
		paths = paths->next;
	}
	return (0);
}