/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:41:55 by seronen           #+#    #+#             */
/*   Updated: 2020/10/21 15:32:42 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned int	hash_gen(const char *key)
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

t_hash		*check_hash(t_hash *head, char *key)
{
	t_hash *tmp;

	tmp = head;
	if (!key)
		ft_error("check_hash: no key or head!");
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return(tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void			*fetch_hash(t_hash **table, char *key)
{
	int index;
	t_hash *fetch;

	index = hash_gen(key);
	if (!(fetch = check_hash(table[index], key)))
		ft_error("fetch_hash: Could not fetch room!");
	free(key);
	return (fetch->room);
}

void	insert_hash(t_lemin *node, char *key, t_room *room)
{
	t_hash *new;
	int index;

	index = hash_gen(key);
	if (check_hash(node->hash[index], key))
		ft_error("insert_hash: Duplicate data not allowed!");
	hashadd(&node->hash[index], hashnew(&key, &room));
}
