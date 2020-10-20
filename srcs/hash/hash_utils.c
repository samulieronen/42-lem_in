/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:01:47 by seronen           #+#    #+#             */
/*   Updated: 2020/10/20 18:03:57 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	hashadd(t_hash **alst, t_hash *new)
{

	if (!alst && !new)
		return ;
	else
	{
		new->next = *alst;
		*alst = new;
	}
}
