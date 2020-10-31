/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:05:12 by seronen           #+#    #+#             */
/*   Updated: 2020/10/31 19:59:58 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_antnbr(t_lemin *node)
{
	node->antnbr++;
	return (node->antnbr);
}

int		init_print(t_lemin *node, t_pathf *paths)
{
	t_pathf *p;

	p = paths;
	node->antnbr = 0;
	node->steps = 1;
	node->goaled = 0;
	while (p)
	{
		p->id_arr = (int*)malloc(sizeof(int) * p->len + 1);
		ft_bzero(p->id_arr, p->len);
		if ((int)p->res > 0)
		{
			p->id_arr[0] = get_antnbr(node);
			ft_printf("arr[0] : %d\n", p->id_arr[0]);
			p->res--;
		}
		p->id_arr[p->len] = 0;
		p = p->next;
	}
	return (0);
}

int		print_ants(t_lemin *node, t_path *p, int *arr, int index)
{
	if (!p)
		return (0);
	if (p->next)
		print_ants(node, p->next, arr, index + 1);
	if (arr[index] && !p->next)
		node->goaled++;
	if (arr[index])
		ft_printf("L%d-%s ", arr[index], p->r->name);
	return (0);
}

int		move_ants(t_lemin *node, t_pathf *p, int *arr)
{
	int i;
	int pos;

	i = 0;
	arr[p->len] = 0;
	pos = 0;
	while (arr[i])
	{
		if (arr[i])
			pos = i;
		i++;
	}
	while (pos > 0 && pos + 1 < p->len)
	{
		arr[pos] = arr[pos + 1];
		arr[pos] = 0;
		pos--;
	}
	if ((int)p->res > 0)
	{
		arr[0] = get_antnbr(node);
		p->res--;
	}
	return (0);
}

int		print_manager(t_lemin *node, t_pathf *paths)
{
	t_pathf *p;

	p = paths;
	while (p)
	{
		move_ants(node, p, p->id_arr);
		p = p->next;
	}
	return (0);
}


int		print_inception(t_lemin *node, t_set *set)
{
	t_pathf *p;

	if (!set)
		ft_error("No best set present! Exiting...", NULL, 0);
	init_print(node, set->paths);
//	ft_printf("print initialized\n");
	while (node->goaled < node->antcount && node->steps < 2)
	{
		p = set->paths;
//		print_manager(node, set->paths);
//		ft_printf("Print managed\n");
		while (p)
		{
			print_ants(node, p->path->next, p->id_arr, 0);
			ft_printf("Next path!\n");
			p = p->next;
		}
//		print_manager(node, set->paths);
		ft_printf("<< step %d\n", node->steps);
		node->steps++;
	}
	return (0);
}