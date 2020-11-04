/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:59:12 by seronen           #+#    #+#             */
/*   Updated: 2020/11/04 15:08:04 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		antcount(t_lemin *node, char *line)
{
	if (!line)
		ft_error("antcount: No line to read!", NULL, 0);
	validate_ants(node, line);
	node->antcount = ft_atoi(line);
	if (node->antcount < 1 || node->antcount > INT32_MAX)
		ft_error("Number of ants impossible!", NULL, node->lnb);
	save_input(node, ft_strdup(line));
	if (line)
		ft_strdel(&line);
	return (0);
}

static int		parse_line(t_lemin *node, char *line)
{
	int	i;

	i = 0;
	if (!line)
		ft_error("No line to parse!", NULL, node->lnb);
	while (line[i] && ALLOW_SPACES && ft_iswhitespace(line[i]))
		i++;
	if (ft_iswhitespace(line[0]) && !ALLOW_SPACES)
		ft_error("Spaces before data!", NULL, node->lnb);
	if (!ft_strcmp(&line[i], "##end"))
		node->mod = 2;
	else if (!ft_strcmp(&line[i], "##start"))
		node->mod = 1;
	else if (!ERROR_COM && line[i] == '#' && line[i + 1] == '#')
		return (0);
	else if (ERROR_COM && line[i] == '#' && line[i + 1] == '#')
		ft_error("Unknown command", line, node->lnb);
	else if (line[i] == '#' && line[i + 1] != '#')
		return (0);
	else if (ft_strchr(line, '-'))
		build_pipes(node, &line[i]);
	else
		build_room(node, &line[i]);
	return (0);
}

static char		*pre_parse(t_lemin *node)
{
	char	*line;
	int		i;
	int		ret;

	line = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		i = 0;
		node->lnb++;
		if (!line)
			break ;
		while (line[i] && ft_iswhitespace(line[i]) && ALLOW_SPACES)
			i++;
		if (ft_iswhitespace(line[0]) && !ALLOW_SPACES)
			ft_error("Whitespaces before data!", NULL, node->lnb);
		if (line[i] != '#')
			break ;
		save_input(node, ft_strdup(line));
		if (line)
			ft_strdel(&line);
	}
	return (line);
}

int				get_input(t_lemin *node)
{
	char	*line;
	int		ret;

	antcount(node, pre_parse(node));
	line = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		node->lnb++;
		if (!line)
			break ;
		save_input(node, ft_strdup(line));
		if (parse_line(node, line))
			ft_error("Parse line failed!", NULL, 0);
		if (line)
			ft_strdel(&line);
	}
	if (!node->rooms || !node->antcount)
		ft_error("Invalid input!", NULL, node->lnb);
	return (0);
}
