/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:36:02 by seronen           #+#    #+#             */
/*   Updated: 2020/10/22 20:16:28 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_set			*setnew(t_lemin *node, t_pathf *p)
{
	t_set *new;

	if (!(new = (t_set*)malloc(sizeof(t_set))))
		ft_error("setnew: malloc failed!");
	new->setarr = (int**)malloc(sizeof(int*) * node->pathcount);
	new->index = 0;
	new->setarr[0] = p->id_arr;
	new->next = NULL;
	return (new);
}

void			add_set(t_lemin *node, t_set **s, t_pathf *p)
{
	t_set *new;

	if (!s || !p)
		return ;
	new = setnew(node, p);
/*	int y = 0;
	while (new->setarr[0][y])
	{
		ft_printf("%d\t", new->setarr[0][y]);
		y++;
	}
	ft_printf("\n"); */
	if (*s)
	{
		new->next = *s;
		*s = new;
	}
	else
		*s = new;
}

int				manage_sets(t_lemin *node, t_pathf *p)
{
	t_pathf *tmp;
	int i;

	tmp = p;
	i = 0;
	while (tmp)
	{
		add_set(node, &node->map->sets, tmp);
		tmp = tmp->next;
	}
	return (0);
}