/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:30:48 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 13:38:12 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_char(va_list arg, t_printf *node)
{
	int c;

	c = va_arg(arg, int);
	while (node->width-- > 1 && !node->minus)
		node->printed += write(1, " ", 1);
	node->printed += write(1, &c, 1);
	while (node->width-- > 0 && node->minus)
		node->printed += write(1, " ", 1);
	return (0);
}
