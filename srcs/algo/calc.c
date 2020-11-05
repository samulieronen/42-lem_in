/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:22:07 by seronen           #+#    #+#             */
/*   Updated: 2020/11/05 14:29:37 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				gather_data(t_lemin *node, t_set *set)
{
	t_pathf	*p;
	int		pnb;

	p = set->paths;
	set->id = node->set_id;
	set->steps_total = 0;
	pnb = 0;
	while (p)
	{
		set->steps_total += p->len;
		pnb++;
		p = p->next;
	}
	set->amount = pnb;
	return (0);
}

static int		math(t_pathf *head, double calc)
{
	t_pathf *p;
	int		max;
	int		moves;

	if (!head)
		ft_error("No head for math!", NULL, 0);
	max = 0;
	p = head;
	while (p)
	{
		p->res = calc - p->len + 1;
		moves = p->res + p->len;
		if (moves > max)
			max = moves;
		p = p->next;
	}
	return (max);
}

int				calc(t_lemin *node, t_set *sets)
{
	t_set	*s;

	s = sets;
	if (!s)
		ft_error("No possible paths!", NULL, 0);
	while (s)
	{
		s->cost = (s->steps_total + node->antcount - 1) / s->amount;
		s->max_moves = math(s->paths, s->cost);
		s = s->next;
	}
	return (0);
}

int				choose_set(t_lemin *node, t_set *sets)
{
	double	min_cost;
	t_set	*s;

	if (!sets)
		ft_error("No possible paths!", NULL, 0);
	s = sets;
	min_cost = s->cost;
	node->best = s;
	while (s)
	{
		if (min_cost > s->cost)
		{
			min_cost = s->cost;
			node->best = s;
		}
		s = s->next;
	}
	if (!node->best)
		ft_error("Could not determine best set!", NULL, 0);
	balance_ants(node, node->best);
	return (0);
}
