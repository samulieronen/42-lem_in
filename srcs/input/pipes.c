/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:50:39 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 20:21:16 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pipe		*newpipe(t_pipe **head, t_room *where)
{
	t_pipe  *p;

	if (!(p = (t_pipe*)malloc(sizeof(t_pipe))))
		return (NULL);
	p->next = NULL;
	p->adj = NULL;
	if (*head)
	{
		p->next = *head;
		*head = p;
	}
	else
		*head = p;
	p->room = where;
	p->cap = 1;
	p->flow = 0;
	return (p);
}

void	pipe_symbiosis(t_room *from, t_room *where)
{
	t_pipe *a;
	t_pipe *b;

	if (!(a = newpipe(&from->pipes, where)))
		ft_error("symbiosis: newpipe failed!");
	if (!(b = newpipe(&where->pipes, from)))
		ft_error("symbiosis: newpipe failed!");
	a->adj = b;
	b->adj = a;
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
	pipe_symbiosis(from, where);
	return (0);
}
