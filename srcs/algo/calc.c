/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:22:07 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 23:24:38 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		calc(t_lemin *node, t_set *s)
{
	t_pathf *p;
	double calc;
	double moves;
	double max;

	if (!s)
		ft_error("calc: no set!");
	calc = (double)(s->steps_total + node->antcount - 1) / s->amount;
	s->cost = calc;
	p = s->paths;
	max = 0;
	while (p)
	{
		p->res = (calc - p->len);
		moves = p->res + p->len;
		if (moves > max)
			max = moves;
		p = p->next;
	}
	s->max_moves = max;
	return (0);
}