/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:52:30 by seronen           #+#    #+#             */
/*   Updated: 2020/09/07 22:54:10 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    ft_error(char *msg)
{
	if (!msg)
		ft_printf("ERROR.\n");
	else
		ft_printf("ERROR: %s\n", msg);
	exit(0);
}

int     main(void)
{
	t_lemin *node;

	if (!(node = (t_lemin*)malloc(sizeof(t_lemin))))
		ft_error("t_lemin malloc failed!\n");
	if (!(node->log = (t_log*)malloc(sizeof(t_log))))
		ft_error("t_log malloc failed!\n");
	node->log->modid = 0;
	node->log->start = 0;
	node->log->end = 0;
	get_input(node);
	pathfinding(node, fetch_modroom(node->rooms, "start"),ft_strdup("start"));
//	ft_printf("The path: %s\n", get_paths(node));
	return (0);
}