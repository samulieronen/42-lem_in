/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:41:55 by seronen           #+#    #+#             */
/*   Updated: 2020/11/01 23:40:23 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static unsigned int		hash_gen(const char *key)
{
	int len;
	unsigned int hash_val;
	int i;

	len = ft_strnlen(key, MAX_KEY);
	hash_val = 0;
	i = 0;
	while (i < len)
	{
		hash_val += key[i];
		hash_val = ((hash_val * key[i]) % TABLE_SIZE);
		i++;
	}
	return (hash_val);
}

static t_hash			*check_hash(t_hash *head, char *key)
{
	t_hash *tmp;

	tmp = head;
	if (!key)
		ft_error("check_hash: no key or head!", NULL, 0);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return(tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void					*fetch_hash(t_hash **table, char *key)
{
	int index;
	t_hash *fetch;

	if (!key || !table)
		return (NULL);
	index = hash_gen(key);
	if (!(fetch = check_hash(table[index], key)))
		return (NULL);
	return (fetch->room);
}

void					insert_hash(t_lemin *node, char *key, t_room *room)
{
	int index;

	index = hash_gen(key);
	room->hash = index;
	if (check_hash(node->hash[index], key))
	{
		if (!ALLOW_DUP_ROOMS)
			ft_error("Duplicate data not allowed!", key, node->lnb);
		return ;
	}
	hashadd(&node->hash[index], hashnew(&key, &room));
}
