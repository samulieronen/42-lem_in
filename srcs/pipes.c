/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:50:39 by seronen           #+#    #+#             */
/*   Updated: 2020/10/21 13:28:24 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pipe		*newpipe(t_pipe **head, t_room *where)
{
	t_pipe  *p;

	if (!(p = (t_pipe*)malloc(sizeof(t_pipe))))
		return (NULL);
	p->next = NULL;
	if (*head)
	{
		p->next = *head;
		*head = p;
	}
	else
		*head = p;
	p->room = where;
	return (p);
}

int		build_pipes(t_lemin *node, char *line, int rev)
{
	t_room  *from;
	t_room  *where;
	int     i;

	i = 0;
	from = fetch_hash(node->hash, ft_strcdup(&line[i], '-'));
	while (line[i] && line[i] != '-')
		i++;
	where = fetch_hash(node->hash, ft_strcdup(&line[i + 1], '-'));
	if (!where || !from)
		ft_error("build_pipes: where or from is NULL!");
	newpipe(&from->pipes, where);
	newpipe(&where->pipes, from);
	return (0);
}
