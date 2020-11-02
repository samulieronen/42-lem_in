/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:22:07 by seronen           #+#    #+#             */
/*   Updated: 2020/11/02 18:50:19 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_sets(t_lemin *node, t_set **alst)
{
	t_set *temp;
	t_set *tempnext;

	node->lnb = node->lnb; // ????
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
	if (!s)
		ft_error("No possible paths!", NULL, 0);
	while (s)
	{
		calc = (double)(s->steps_total + node->antcount - 1) / s->amount;
		s->cost = calc;
		p = s->paths;
		max = 0;
		if (!p)
			return (0);
		while (p)
		{
//			ft_printf("p-len on %d\n", p->len);
//			ft_printf("calc on %lf\n", calc);
			p->res = calc - p->len + 1;
//			ft_printf("p-res on %d\n", p->res);
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
	if (!node->best)
		ft_error("Could not determine best set!", NULL, 0);
	return (0);
}
