/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:36:02 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 20:48:03 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*new_set(t_set **alst)
{
	t_set *new;

	if (!(new = (t_set*)malloc(sizeof(t_set))))
		ft_error("new_set: Malloc failed!");
	new->paths = NULL;
	new->next = NULL;
	if (*alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	else if (new)
		*alst = new;
	return (0);
}

int		path_to_set(t_path *head, t_pathf **alst, int len)
{
	t_pathf *new;

	new = (t_pathf*)malloc(sizeof(t_pathf));
	new->path = head;
	new->len = len;
	if (!new)
		ft_error("path_to_set: Malloc failed!");
	if (*alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	if (new)
		*alst = new;
	return (0);
}

t_path	*path_new(t_room *r)
{
	t_path *new;

	new = (t_path*)malloc(sizeof(t_path));
	if (!new)
		ft_error("path_new: Malloc failed!");
	if (!r)
		ft_error("path_new: no room to add!");
	new->r = r;
	new->next = NULL;
	return (new);
}

int		add_path(t_path **alst, t_path *new)
{
	if (*alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	else if (new)
		*alst = new;
	return (0);
}