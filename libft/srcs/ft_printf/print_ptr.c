/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:05:21 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 13:27:26 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_ptr(va_list arg, t_printf *node)
{
	char				*res;
	int					i;

	if (!(res = ft_itoa_base(va_arg(arg, unsigned long long), 16)))
		exit(-1);
	if (!node->width || (size_t)node->width < ft_strlen(res) + 2)
		res = addchar(res, 0);
	if (node->width && ft_strlen(res) < (size_t)node->width)
	{
		if (!node->zero)
		{
			res = addchar(res, 0);
			res = width(res, node, ' ', node->width);
		}
		else
		{
			res = width(res, node, '0', node->width - 2);
			res = addchar(res, 0);
		}
	}
	i = 0;
	while (res[i])
		node->printed += write(1, &res[i++], 1);
	free(res);
	return (0);
}
