/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 23:55:56 by seronen           #+#    #+#             */
/*   Updated: 2020/11/04 13:43:32 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		validate_ants(t_lemin *node, char *line)
{
	int i;

	i = 0;
	if (!line)
		ft_error("Invalid input!", NULL, node->lnb);
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			ft_error("Invalid number of ants!", line, node->lnb);
		i++;
	}
}

void		validate_room(t_lemin *node, char *line)
{
	int i;

	i = 0;
	if (ERROR_L && line[0] == 'L')
		ft_error("Bad symbol in room name!", line, node->lnb);
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && !ft_iswhitespace(line[i]))
			ft_error("Invalid room name", line, node->lnb);
		i++;
	}
	if (ft_iswhitespace(line[i - 1]))
		ft_error("Whitespaces in data!", line, node->lnb);
}

void		validate_pipe(t_lemin *node, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	if (!line[i] || !line[i + 1])
		ft_error("Invalid pipe!", line, node->lnb);
	while (line[i])
	{
		if (ft_iswhitespace(line[i]))
			ft_error("Whitespaces in data!", line, node->lnb);
		i++;
	}
}
