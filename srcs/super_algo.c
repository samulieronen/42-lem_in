/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:09:59 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 16:22:01 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*fetch_id(t_lemin *node, int id)
{
	t_room *tmp;
	
	tmp = node->rooms;
	if (!tmp)
		return (NULL);
//	ft_printf("id : %d\n", id);
	while (tmp)
	{
		if (tmp->id == id)
		{
//			ft_printf("fetch ID found id %d\n", tmp->id);
			return (tmp);
		}
		tmp = tmp->next;
	}
//	ft_printf("Umm fetch id not functioning\n");
	return (NULL);
}

int		*shortest_path(t_pathf *head)
{
	t_pathf *tmp;
	t_pathf *res;
	int shortest;
	int *arr;
	int	cur;

	tmp = head;
	shortest = 100000;
	if (!tmp)
	{
		return (NULL);
	}
	arr = NULL;
	while (tmp)
	{
		if (tmp->id_arr[0] && tmp->len < shortest)
		{
			shortest = tmp->len;
			res = tmp;
		}
		tmp = tmp->next;
	}
	ft_printf("\nshortest len: %d\n\n", res->len);
	return (res->id_arr);
}

int		anti_augment(t_lemin *node, int *arr, int index)
{
	int i;
	t_room *a;
	t_room *b;
	t_pipe *tmp;
	t_pipe *real;

	i = index;
	if (!arr)
		return (-1);
	ft_printf("ANTI AUGMENT\n");
	while (i > 0 && arr[i - 1])
	{
		a = fetch_id(node, arr[i]);
		ft_printf("a-a: %s\n", a->name);
		b = fetch_id(node, arr[i - 1]);
		ft_printf("a-b: %s\n", b->name);
		if (!a || !b)
			ft_error("Bruu super_algo failed!");
		tmp = a->pipes;
		real = NULL;
		while (tmp)
		{
			if (tmp->room && tmp->room->id == b->id)
			{
				real = tmp;
				break ;
			}
			tmp = tmp->next;
		}
		if (!real)
			ft_error("error no pipe!");
		real->flow += 1;
		real->adj->flow -= -1;
		i--;
	}
	return (1);
}

int		augment(t_lemin *node, int *arr)
{
	int i;
	t_room *a;
	t_room *b;
	t_pipe *tmp;
	t_pipe *real;

	i = 0;
	if (!arr)
		return (-1);
	ft_printf("AUGMENT\n");
	while (arr[i + 1])
	{
		a = fetch_id(node, arr[i]);
		ft_printf("a: %s\n", a->name);
		b = fetch_id(node, arr[i + 1]);
		ft_printf("b: %s\n", b->name);
		if (!a || !b)
			ft_error("Bruu super_algo failed!");
//		ft_printf("fetch'd rooms\n");
		tmp = a->pipes;
		real = NULL;
		while (tmp)
		{
			if (tmp->room && tmp->room->id == b->id)
			{
				real = tmp;
				break ;
			}
			tmp = tmp->next;
		}
		if (!real)
			ft_error("error no pipe!");
		if (real->flow == 1)
		{
			anti_augment(node, arr, i);
			arr[0] = 0;
			return (1);
		}
//		ft_printf("flow OK, augmenting\n");
		real->flow += 1;
		real->adj->flow -= -1;
		i++;
	}
	arr[0] = 0;
	return (0);
}

int     super_algo(t_lemin *node)
{
	int i;
	int flow;
	t_set *set;
	int ret;

	i = node->antcount;
	node->v_token = 1;
	node->m_token = 1;
	flow = 0;
	int *arr;
	arr = (int*)malloc(sizeof(int) * node->roomnb + 1);
	ft_bzero(arr, node->roomnb);
	pathfinding(node, node->start, arr, 0);
	t_pathf *tmp = node->map->paths;
	while (tmp)
	{
		ft_printf("Path found, len : %d\n", tmp->len);
		int f = 0;
		while (tmp->id_arr[f])
		{
			ft_printf("%d ", tmp->id_arr[f]);
			f++;
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("\n");
	node->v_token += 1;
//	ft_printf("After pathfinding\n");
	while (i)
	{
//		ft_printf("Before augment\n");
		while ((ret = augment(node, shortest_path(node->map->paths)) > 0))
			if (ret == -1)
				ft_error("YAYA problem in augment");
		ft_printf("\n\n");
//		ft_printf("augment OK\n");
//		ft_printf("Before bfs\n");
		graph_path(node, NULL, set, &flow);
		node->m_token += 1;
		node->v_token += 1;
		i--;
		ft_printf("\nNEW\n");
	}
	return (0);
}