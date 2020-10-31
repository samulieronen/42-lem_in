/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:59:12 by seronen           #+#    #+#             */
/*   Updated: 2020/10/31 23:51:59 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     antcount(t_lemin *node, char *line)
{
	if (!line)
		ft_error("antcount: No line to read!", NULL, 0);
	node->antcount = ft_atoi(line);
	if (node->antcount < 1 || node->antcount > INT32_MAX)
		ft_error("Number of ants impossible!", NULL, node->lnb);
	save_input(node, ft_strdup(line));
	if (line)
		ft_strdel(&line);
	return (0);
}

int     parse_line(t_lemin *node, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' && ALLOW_SPACES)
		i++;
	if (line[0] == ' ' && !ALLOW_SPACES)
		ft_error("Spaces before data!", NULL, node->lnb);
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

char		*pre_parse(t_lemin *node)
{
	char *line;
	int i;

	while (get_next_line(0, &line) > 0)
	{
		i = 0;
		node->lnb++;
		if (!line || line[0] == '\0')
			break ;
		while (line[i] && line[i] == ' ' && ALLOW_SPACES)
			i++;
		if (line[i] == ' ' && !ALLOW_SPACES)
			ft_error("Spaces before data!", NULL, node->lnb);
		if (line[i] != '#')
			break ;
		save_input(node, ft_strdup(line));
		if (line)
			ft_strdel(&line);
	}
	return (line);
}

int     get_input(t_lemin *node)
{
	char    *line;
	
	antcount(node, pre_parse(node));
	while (get_next_line(0, &line) > 0)
	{
		node->lnb++;
		if (!line || line[0] == '\0')
			break ;
		save_input(node, ft_strdup(line));
		if (parse_line(node, line))
			ft_error("Parse line failed!", NULL, 0);
		if (line)
			ft_strdel(&line);
	}
	if (!node->rooms || !node->antcount)
		ft_error("Empty line or invalid input!", NULL, node->lnb);
	return (0);
}
