/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:52:30 by seronen           #+#    #+#             */
/*   Updated: 2020/10/30 13:34:42 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_error(char *msg)
{
	if (!msg)
		ft_printf("ERROR.\n");
	else
		ft_printf("ERROR: %s\n", msg);
	exit(-42);
}

void			ft_input_error(char *msg, char *s1, int lnbr)
{
	ft_printf("lem-in:\t");
	if (!msg)
		ft_printf("ERROR.\n");
	else if (lnbr && !s1)
		ft_printf("ERROR: Line %d:\t%s\n", lnbr, msg);
	else
	{
		ft_printf(RED "ERROR ");
		ft_printf(RESET "on line %d:\t%s '%s'\n", lnbr, msg, s1);
	}
	exit(-42);
}

static t_lemin		*setup_structs(void)
{
	t_lemin *node;

	if (!(node = (t_lemin*)malloc(sizeof(t_lemin))))
		ft_error("t_lemin malloc failed!");
//	if (!(node->map = (t_map*)malloc(sizeof(t_map))))
//		ft_error("t_map malloc failed!");
	ft_bzero(node->hash, TABLE_SIZE);
	node->roomnb = 0;
	node->line_nb = 0;
	node->pathcount = 0;
//	node->map->paths = NULL;
//	node->map->max_paths = 0;
//	node->map->max_moves = 0;
	node->rooms = NULL;
	node->pathf = NULL;
	node->sets = NULL;
	node->ants = NULL;
	node->antcount = 0;
	return (node);
}

int				main(void)
{
	t_lemin *node;

	node = setup_structs();
	get_input(node);
	if (!node->start || !node->end)
		ft_error("No start or end room present!");
	if (!node->start->pipes || !node->end->pipes)
		ft_error("No possible path!");
	ft_printf("\nFinding\n");
	ft_printf("node->start->name: %s\n", node->start->name);
	ft_printf("node->start->id: %d\n", node->start->id);
	ft_printf("node->end->name: %s\n\n", node->end->name);
	if (PRINT_IN)
		ft_printf("\n\n");
	if (SUPER)
		super_algo(node);
	else
		solve(node);
	if (LEAKS)
		system("leaks lem-in");
	return (0);
}
