/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:05:12 by seronen           #+#    #+#             */
/*   Updated: 2020/11/05 17:15:18 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		print_ants(t_lemin *node, t_path *p, int *arr)
{
	t_path	*tmp;
	int		i;

	i = 0;
	tmp = p;
	while (tmp)
	{
		if (P_END_CLR && arr[i] && P_OUTPUT && tmp->r->id == node->end->id)
			ft_printf("L%d-"GREEN"%s "RESET, arr[i], tmp->r->name);
		else if (arr[i] && P_OUTPUT)
			ft_printf("L%d-%s ", arr[i], tmp->r->name);
		if (arr[i] && !tmp->next)
			node->goaled++;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

static int		move_ants(t_lemin *node, t_pathf *p, int *arr)
{
	int i;
	int pos;

	i = 0;
	arr[p->len] = 0;
	pos = 0;
	while (i < p->len)
	{
		if (arr[i] != 0)
			pos = i;
		i++;
	}
	while (pos >= 0)
	{
		arr[pos + 1] = arr[pos];
		arr[pos] = 0;
		pos--;
	}
	if (p->res > 0 && node->antnbr < node->antcount)
	{
		arr[0] = get_antnbr(node);
		p->res--;
	}
	return (0);
}

static int		print_manager(t_lemin *node, t_pathf *paths)
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

int				print_output(t_lemin *node, t_set *set)
{
	t_pathf *p;

	if (!set)
		ft_error("No best set present! Exiting...", NULL, 0);
	init_print(node, set->paths);
	p = set->paths;
	while (node->goaled < node->antcount)
	{
		p = set->paths;
		while (p)
		{
			print_ants(node, p->path->next, p->id_arr);
			p = p->next;
		}
		if (P_OUTPUT)
			ft_putchar('\n');
		print_manager(node, set->paths);
		if (node->goaled < node->antcount)
			node->steps++;
	}
	return (0);
}
