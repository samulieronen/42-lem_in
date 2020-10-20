/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:52:30 by seronen           #+#    #+#             */
/*   Updated: 2020/10/20 16:51:15 by seronen          ###   ########.fr       */
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

static t_lemin		*setup_structs(void)
{
	t_lemin *node;

	if (!(node = (t_lemin*)malloc(sizeof(t_lemin))))
		ft_error("t_lemin malloc failed!");
	if (!(node->log = (t_log*)malloc(sizeof(t_log))))
		ft_error("t_log malloc failed!");
	if (!(node->map = (t_map*)malloc(sizeof(t_map))))
		ft_error("t_map malloc failed!");
	init_hash(node);
	node->log->modid = 0;
	node->roomnb = 0;
	node->map->max_paths = 0;
	node->map->max_moves = 0;
	node->rooms = NULL;
	node->pathf = NULL;
	node->sets = NULL;
	node->ants = NULL;
	node->antcount = 0;
	node->log->start = 0;
	node->log->end = 0;
	return (node);
}

int				main(void)
{
	t_lemin *node;

	node = setup_structs();
	get_input(node);
	make_ants(node);
	pathfinding(node, node->start, ft_strdup(""));
	t_pathf *temp = node->map->paths;
	while (temp)
	{
		ft_printf("Found path: %s\n", temp->path);
		ft_printf("\n");
		temp = temp->next;
	}
//	while (1);
	ft_printf("\n");
	if (CHOOSER == 1)
		pathchooser2(node, node->map);
	else
		pathchoosing(node);
	return (0);
}
