/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:33:18 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 13:57:18 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*handle_zero(char *str, t_printf *node)
{
	if ((str[0] == '0' && str[1] == '\0') && !node->dot && node->hash)
		node->hash = 0;
	if ((str[0] == '0' && str[1] == '\0') && node->dot && node->hash)
	{
		node->hash = 0;
		return (str);
	}
	if ((str[0] != '0' || str[1] != '\0') || !node->dot)
		return (str);
	else
	{
		node->hash = 0;
		free(str);
		return (ft_strnew(0));
	}
}

static char			*get_arg_oct(va_list arg, t_printf *node)
{
	unsigned long long nb;

	nb = 0;
	if (!node->length)
		nb = (unsigned int)va_arg(arg, unsigned int);
	else if (!ft_strcmp(node->length, "ll"))
		nb = (unsigned long long)va_arg(arg, unsigned long long);
	else if (!ft_strcmp(node->length, "l"))
		nb = (unsigned long)va_arg(arg, unsigned long);
	else if (!ft_strcmp(node->length, "h"))
		nb = (unsigned short)va_arg(arg, unsigned int);
	else if (!ft_strcmp(node->length, "hh"))
		nb = (unsigned char)va_arg(arg, unsigned int);
	else if (!ft_strcmp(node->length, "z"))
		nb = (size_t)va_arg(arg, size_t);
	else
		exit(-1);
	if (node->dot && !node->precision && node->zero)
		node->zero = 0;
	return (ft_itoa_base(nb, 8));
}

int					print_octal(va_list arg, t_printf *node)
{
	int		i;
	char	*res;

	i = 0;
	if (!(res = get_arg_oct(arg, node)))
		exit(-1);
	res = handle_zero(res, node);
	if ((node->minus || node->precision) && node->zero)
		node->zero = 0;
	if (node->hash)
		res = addchar(res, '0');
	if (node->precision && ((int)ft_strlen(res) < node->precision))
		res = precision(res, node, node->precision);
	if (node->width && (int)ft_strlen(res) < node->width)
	{
		if (!node->zero)
			res = width(res, node, ' ', node->width);
		else
			res = width(res, node, '0', node->width);
	}
	while (res[i])
		node->printed += write(1, &res[i++], 1);
	free(res);
	return (0);
}
