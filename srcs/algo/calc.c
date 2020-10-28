/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:22:07 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 17:03:32 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		calc(t_lemin *node)
{
	t_set *s;
	t_pathf *p;
	double calc;
	double moves;
	double max;

	s = node->sets;
	calc = 0;
	printf("%lf\n", (double)1/2);
	while (s)
	{
		calc = (double)(s->steps_total + node->antcount - 1) / s->amount;
		printf("calc = %d + %lld - 1 / %d = %lf\n", s->steps_total, node->antcount, s->amount, (double)calc);
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
//		printf("min moves: %f calc : %f\n", max, calc);
		s = s->next;
	}
	return (0);
}