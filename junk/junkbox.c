/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junkbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:52:28 by seronen           #+#    #+#             */
/*   Updated: 2020/10/31 22:25:16 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	while (node->rooms)
	{
		printf("Found room %s\n", node->rooms->name);
		if (node->rooms->info)
			printf("%s\n", node->rooms->info);
		while (node->rooms->pipes)
		{
			printf("Pipe to '%s'\n", node->rooms->pipes->where);
			node->rooms->pipes = node->rooms->pipes->next;
		}
		printf("\n");
		node->rooms = node->rooms->next;
	}
	ft_printf("\n\n");
    

int		q_offer2(t_lemin *node, t_queue *q, t_parent *par)
{
	t_pipe *tmp;
	t_pipe *from;
	int nb;

	tmp = q->room->pipes;
	from = get_last(par, q->room);
	nb = 0;
	if (from && from->flow == 0)
	{
		ft_printf("Last edges flow was 0 | pipe from %s to %s\n", from->adj->room->name, from->room->name);
		while (tmp)
		{
			if (tmp->room->id == node->start->id || q_check(node, q, tmp->room))
				ft_printf("room %s failed for being start or allready in queue\n", tmp->room->name);
			else if (tmp->room->flag && tmp->room->visited < node->v_token)
			{
				if (!(ensure_flow(node, tmp->room)))
				{
					nb++;
					q_add(&q, tmp->room);
					q_parent(par, tmp);
					ft_printf("Ensure flow added room %s\n", tmp->room->name);
				}
				ft_printf("Ensure flow failed for room %s\n", tmp->room->name);
			}
			else if (tmp->room->visited < node->v_token)
			{
				nb++;
				q_add(&q, tmp->room);
				q_parent(par, tmp);
				ft_printf("Added %s to queue\n", tmp->room->name);
			}
			ft_printf("Nasta pipen\n");
			tmp = tmp->next;
		}
		return (0);
	}
	tmp = q->room->pipes;
	ft_printf("Last edges flow was not 0\n");
	while (tmp)
	{
		if (tmp->flow > 0 || tmp->room->visited >= node->v_token || q_check(node, q, tmp->room))
			tmp = tmp->next;
		else
		{
			nb++;
			q_add(&q, tmp->room);
			q_parent(par, tmp);
			tmp = tmp->next;
		}
	}
	return (nb + 1);
}

*/
