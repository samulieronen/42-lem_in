/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:52:30 by seronen           #+#    #+#             */
/*   Updated: 2020/09/17 02:36:30 by seronen          ###   ########.fr       */
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
	t_pathf *tmp;

	if (!(node = (t_lemin*)malloc(sizeof(t_lemin))))
		ft_error("t_lemin malloc failed!\n");
	if (!(node->log = (t_log*)malloc(sizeof(t_log))))
		ft_error("t_log malloc failed!\n");
	node->log->modid = 0;
	node->rooms = NULL;
	node->pathf = NULL;
	node->sets = NULL;
	node->ants = NULL;
	node->antcount = 0;
	node->log->start = 0;
	node->log->end = 0;
	get_input(node);
	make_ants(node);
	pathfinding(node, fetch_modroom(node->rooms, "start"), ft_strdup(""));		// Neue pathfinding algo!
//	ft_printf("The path: %s\n", get_paths(node)); 					// Old and grumpy pathfinding algo!
	pathchoosing(node);
//	tmp = node->pathf;
//	int nb = 1;
//	while (tmp)
//	{
//		ft_printf("Path %d: %s | len: %d\n", nb, tmp->path, tmp->len);
//		if (!tmp->crossing)
//			ft_printf("Path not crossing with any other path\n\n");
//		tmp = tmp->next;
//		nb++;
//	}
//	while (node->ants)
//	{
//		ft_printf("antnb: %d\n", node->ants->antnb);
//		node->ants = node->ants->next;
//	}
	return (0);
}