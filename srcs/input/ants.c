/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 02:25:04 by seronen           #+#    #+#             */
/*   Updated: 2020/10/29 12:00:00 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     make_ants(t_lemin *node)
{
	int ac;
	int nb;
	t_ant *tmp;
	t_ant *head;

	return (0);
	nb = 1;
	ac = node->antcount;
	tmp = (t_ant*)malloc(sizeof(t_ant));
	tmp->antnb = nb++;
	head = tmp;
	ac--;
	while (ac > 0)
	{
		tmp->next = (t_ant*)malloc(sizeof(t_ant));
		tmp = tmp->next;
		tmp->antnb = nb++;
		ac--;
	}
	tmp->next = NULL;
	node->ants = head;
	return (0);
}