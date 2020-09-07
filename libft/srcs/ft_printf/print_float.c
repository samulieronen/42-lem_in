/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:19:21 by seronen           #+#    #+#             */
/*   Updated: 2020/02/26 14:37:04 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*handle_space_float(t_printf *node, char *str)
{
	char *res;

	if (!node->space || node->plus || node->sign)
		return (str);
	res = ft_strjoin(" ", str);
	free(str);
	node->space = 0;
	return (res);
}

static char		*putdot(char *str)
{
	char *res;

	res = ft_strjoin(str, ".");
	free(str);
	return (res);
}

static char		*get_arg_float(va_list arg, t_printf *node)
{
	long double nb;

	nb = 0;
	if (!node->length)
		nb = (double)va_arg(arg, double);
	else if (!ft_strcmp(node->length, "l"))
		nb = (double)va_arg(arg, double);
	else if (!ft_strcmp(node->length, "L"))
		nb = (long double)va_arg(arg, long double);
	else
		exit(-1);
	node->sign = (nb < 0) ? 1 : 0;
	if (node->plus && nb >= 0)
		node->sign = 2;
	nb *= (nb < 0) ? -1 : 1;
	if (!node->precision && !node->dot)
	{
		node->precision = 6;
		node->fprecision = 1;
	}
	if (node->zero && node->minus)
		node->zero = 0;
	return (ft_ftoa(nb, node->precision));
}

int				print_float(va_list arg, t_printf *node)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = get_arg_float(arg, node)))
		exit(-1);
	if (node->sign == 1 && node->plus)
		node->plus = 0;
	if (node->hash && node->dot && !node->precision)
		res = putdot(res);
	if (node->space && !node->zero)
		res = handle_space_float(node, res);
	if (node->width)
	{
		if (!node->zero)
			res = width(res, node, ' ', node->width - node->sign);
		else
			res = width(res, node, '0', node->width - node->sign);
	}
	res = manage_plus_minus(node, res);
	res = handle_space(node, res);
	while (res[i])
		node->printed += write(1, &res[i++], 1);
	free(res);
	return (0);
}
