/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:01:47 by seronen           #+#    #+#             */
/*   Updated: 2020/10/21 00:32:35 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	hashadd(t_hash **alst, t_hash *new)
{
	if (*alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	else if (new)
		*alst = new;
}

t_hash	*hashnew(char **key, t_room **room)
{
	t_hash *new;

	new = (t_hash*)malloc(sizeof(t_hash));
	new->key = *key;
	new->room = *room;
	new->next = NULL;
	return (new);
}
