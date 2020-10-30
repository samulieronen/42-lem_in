/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:22:07 by seronen           #+#    #+#             */
/*   Updated: 2020/10/30 16:57:46 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_sets(t_lemin *node, t_set **alst)
{
	t_set *temp;
	t_set *tempnext;

	node->line_nb = node->line_nb;
	temp = *alst;
	if (!alst)
		return ;
	while (temp)
	{
		tempnext = temp->next;
		free(temp);
		temp = tempnext;
	}
	*alst = NULL;
}

int		gather_data(t_lemin *node, t_set *set)
{
	t_pathf *p;
	int pnb;

	p = set->paths;
	set->id = node->set_id;
	set->steps_total = 0;
	pnb = 0;
	while (p)
	{
		set->steps_total +=p->len;
		pnb++;
		p = p->next;
	}
	set->amount = pnb;
	return (0);
}

int		calc(t_lemin *node, t_set *sets)
{
	t_pathf *p;
	t_set *s;
	double calc;
	double moves;
	double max;

	s = sets;
	while (s)
	{
		if (!s)
			ft_error("calc: no set!");
		calc = (double)(s->steps_total + node->antcount - 1) / s->amount;
		s->cost = calc;
		p = s->paths;
		max = 0;
		if (!p)
			ft_error("calc: Set has no paths!");
		while (p)
		{
			p->res = (calc - p->len);
			moves = p->res + p->len;
			if (moves > max)
				max = moves;
			p = p->next;
		}
		s->max_moves = max;
		s = s->next;
	}
	return (0);
}

int		choose_set(t_lemin *node, t_set *sets)
{
	double min_cost;
	t_set *s;

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
	ft_printf("lines: %d\n", (int)min_cost);
	if (!node->best)
		ft_error("Could not determine best set!");
	return (0);
	free_sets(node, &node->sets);
	while (node->best->paths)
	{
		ft_printf("Path len: %d\n", node->best->paths->len);
		node->best->paths = node->best->paths->next;
	}
	return (0);
}
