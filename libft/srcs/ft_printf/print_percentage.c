/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percentage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:37:45 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 13:27:43 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_percentage(t_printf *node)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = ft_strdup("%")))
		exit(-1);
	if (node->minus && node->zero)
		node->zero = 0;
	if (node->width > 1)
	{
		if (!node->zero)
			res = width(res, node, ' ', node->width - node->sign);
		else
			res = width(res, node, '0', node->width - node->sign);
	}
	while (res[i])
		node->printed += write(1, &res[i++], 1);
	free(res);
	return (0);
}
