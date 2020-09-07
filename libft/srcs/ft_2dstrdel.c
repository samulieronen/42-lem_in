/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstrdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:28:25 by seronen           #+#    #+#             */
/*   Updated: 2020/03/09 14:30:39 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_2dstrdel(char **as)
{
	int i;

	if (as != NULL)
	{
		i = 0;
		while (as[i])
		{
			free(as[i]);
			as[i] = NULL;
			i++;
		}
		free(as);
		as = NULL;
	}
}
