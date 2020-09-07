/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:33:14 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 14:11:46 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*handle_zero(char *str, t_printf *node)
{
	if ((str[0] != '0' || str[1] != '\0') || !node->dot)
		return (str);
	else
	{
		node->zero = 0;
		node->hash = 0;
		free(str);
		return (ft_strnew(0));
	}
}

static char		*add_precision(char *str, t_printf *node, size_t nb)
{
	char	*new;
	char	*res;

	new = strnew_char(nb, '0');
	res = ft_strjoin(new, str);
	free(str);
	free(new);
	if (!node->precision)
	{
		free(res);
		res = ft_strnew(1);
	}
	return (res);
}

static char		*diprecision(char *str, t_printf *node)
{
	char	*new;

	new = add_precision(str, node, node->precision - ft_strlen(str));
	if ((size_t)node->width < ft_strlen(new))
		node->width = 0;
	return (new);
}

static char		*get_arg_dec(va_list arg, t_printf *node)
{
	long long nb;

	nb = 0;
	if (!node->length)
		nb = (int)va_arg(arg, int);
	else if (!ft_strcmp(node->length, "ll"))
		nb = (long long)va_arg(arg, long long);
	else if (!ft_strcmp(node->length, "l"))
		nb = (long)va_arg(arg, long);
	else if (!ft_strcmp(node->length, "h"))
		nb = (short)va_arg(arg, int);
	else if (!ft_strcmp(node->length, "z"))
		nb = (size_t)va_arg(arg, size_t);
	else if (!ft_strcmp(node->length, "hh"))
		nb = (signed char)va_arg(arg, int);
	else
		exit(-1);
	node->sign = (nb < 0) ? 1 : 0;
	if (node->plus && nb >= 0)
		node->sign = 2;
	nb *= (nb < 0) ? -1 : 1;
	return (ft_itoa_base(nb, 10));
}

int				print_dec(va_list arg, t_printf *node)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = get_arg_dec(arg, node)))
		exit(-1);
	if ((node->minus || node->precision) && node->zero)
		node->zero = 0;
	res = handle_zero(res, node);
	if (node->precision && (int)ft_strlen(res) < node->precision)
		res = diprecision(res, node);
	if (node->width)
	{
		if (!node->zero)
			res = width(res, node, ' ', node->width - node->sign);
		else
			res = width(res, node, '0', node->width - node->sign);
	}
	res = handle_space(node, res);
	res = manage_plus_minus(node, res);
	while (res[i])
		node->printed += write(1, &res[i++], 1);
	free(res);
	return (0);
}
