/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:33:38 by seronen           #+#    #+#             */
/*   Updated: 2020/11/01 23:38:59 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_lines(t_lemin *node)
{
	t_input	*input;
	t_input	*del;
	int		i;

	if (!node->input)
		ft_error("No input present!", NULL, 0);
	input = node->input;
	while (input)
	{
		i = 0;
		del = input;
		while (i < MAX_SIZE && input->line[i])
		{
			ft_putendl(input->line[i]);
			ft_strdel(&input->line[i]);
			i++;
		}
		input = input->next;
		free(del);
	}
	ft_putendl("\n");
	node->input = NULL;
}


static t_input	*new_input(t_lemin *node)
{
	t_input	*new;
	t_input	*tmp;
	t_input	*head;

	head = node->input;
	if (!(new = (t_input*)malloc(sizeof(t_input))))
		ft_error("new_input: Malloc failed!", NULL, 0);
	new->next = NULL;
	new->index = 0;
	ft_bzero(new->line, MAX_SIZE);
	tmp = head;
	if (!head)
	{
		head = new;
		head->next = NULL;
		node->input = head;
		return (head);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->next = NULL;
	}
	return (tmp->next);
}

int				save_input(t_lemin *node, char *line)
{
	t_input	*tmp;

	tmp = node->input;
	if (line[0] == '\0' && !ALLOW_EMPTY_LINES)
		ft_error("Invalid input!", NULL, node->lnb);
	if (!tmp || tmp->index == MAX_SIZE)
	{
		tmp = new_input(node);
		tmp->line[tmp->index] = line;
		tmp->index++;
	}
	else
	{
		tmp->line[tmp->index] = line;
		tmp->index++;
	}
	return (0);
}