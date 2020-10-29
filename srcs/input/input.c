/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:59:12 by seronen           #+#    #+#             */
/*   Updated: 2020/10/29 23:49:37 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     antcount(t_lemin *node)
{
	char *line;

	if (get_next_line(0, &line) < 0)
		ft_error("Invalid file");
	node->line_nb++;
	node->antcount = ft_atoi(line);
	if (node->antcount < 1 || node->antcount > INT32_MAX)
		ft_input_error("Number of ants impossible!", NULL, node->line_nb);
	if (PRINT_IN)
		ft_printf("%s\n", line);
	ft_strdel(&line);
	return (0);
}

int     parse_line(t_lemin *node, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (!ft_strcmp(line, "##end"))
		node->mod = 2;
	else if (!ft_strcmp(line, "##start"))
		node->mod = 1;
	else if (line[i] == '#' && line[i + 1] != '#')
		return (0);
	else if (ft_strchr(line, '-'))
		build_pipes(node, line);
	else
		build_room(node, line);
	return (0);
}

int     get_input(t_lemin *node)
{
	char    *line;

	antcount(node);
	while (get_next_line(0, &line) > 0)
	{
		node->line_nb++;
		if (!line)
			break ;
		if (PRINT_IN)
			ft_putendl(line);
		if (parse_line(node, line))
			ft_error("Parse line failed!");
		if (line)
			ft_strdel(&line);
	}
	return (0);
}
