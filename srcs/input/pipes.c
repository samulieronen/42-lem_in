/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:50:39 by seronen           #+#    #+#             */
/*   Updated: 2020/10/31 20:04:00 by seronen          ###   ########.fr       */
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
		ft_error("symbiosis: newpipe failed!", NULL, 0);
	if (!(b = newpipe(&where->pipes, from)))
		ft_error("symbiosis: newpipe failed!", NULL, 0);
	a->adj = b;
	b->adj = a;
}

int		build_pipes(t_lemin *node, char *line)
{
	t_room  *from;
	t_room  *where;
	char	*str;
	int     i;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	line[i] = '\0';
	str = &line[i + 1];
	if (!(from = fetch_hash(node->hash, &line[0])))
		ft_error("No room named", &line[0], node->lnb);
	if (!(where = fetch_hash(node->hash, str)))
		ft_error("No room named", str, node->lnb);
	if (!ALLOW_SELF_LINKING && where->id == from->id)
		ft_error("Self-linking pipe not allowed! =", str, node->lnb);
	pipe_symbiosis(from, where);
	return (0);
}
