/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:41:55 by seronen           #+#    #+#             */
/*   Updated: 2020/10/20 01:24:37 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned int	hash_gen(char *key)
{
	int len;
	unsigned int hash_val;
	int i;

	len = ft_strnlen(key, MAX_LEN);
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

int				hash_insert(t_hash *hash, char *key, void *data)
{
	int index;
	char **table;

	table = hash->hashtable;
	index = hash_gen(key);
	return (0);
}

void			hash_fetch(t_hash *hash, char *key)
{
	char *arr;
	
}

int				main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
		return (0);
	while (i < ac)
	{
		ft_printf("Hash of %s: %u\n", av[i], hash(av[i]));
		i++;
	}
	return (0);
}
