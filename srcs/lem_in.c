/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:52:30 by seronen           #+#    #+#             */
/*   Updated: 2020/10/31 23:19:36 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_error(char *msg, char *s1, int lnbr)
{
	ft_printf("lem-in:\t");
	ft_printf(RED "ERROR ");
	if (!s1 && !lnbr)
		ft_printf(RESET "%s\n", msg);
	else if (lnbr && !s1)
		ft_printf(RESET "on line %d: %s\n", lnbr, msg);
	else
		ft_printf(RESET "on line %d: %s '%s'\n", lnbr, msg, s1);
	exit(-42);
}

static t_lemin		*setup_structs(void)
{
	t_lemin *node;

	if (!(node = (t_lemin*)malloc(sizeof(t_lemin))))
		ft_error("t_lemin malloc failed!", NULL, 0);
	ft_bzero(node->hash, TABLE_SIZE);
	node->roomnb = 0;
	node->lnb = 0;
	node->pathcount = 0;
	node->rooms = NULL;
	node->sets = NULL;
	node->antcount = 0;
	return (node);
}

int				main(void)
{
	t_lemin *node;

	node = setup_structs();
	get_input(node);
	if (!node->start || !node->end)
		ft_error("No start or end room present!", NULL, 0);
	if (!node->start->pipes || !node->end->pipes)
		ft_error("No possible path!", NULL, 0);
	if (P_INPUT)
		print_lines(node);
	solve(node);
	if (LEAKS)
		system("leaks lem-in");
	return (0);
}
