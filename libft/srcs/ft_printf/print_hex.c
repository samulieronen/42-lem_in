/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:29:11 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 13:37:28 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*handle_zero(char *str, t_printf *node)
{
	if ((str[0] == '0' && str[1] == '\0') && !node->dot && node->hash)
		node->hash = 0;
	if ((str[0] != '0' || str[1] != '\0') || !node->dot)
		return (str);
	else
	{
		node->hash = 0;
		free(str);
		return (ft_strnew(0));
	}
}

static char		*get_arg_hex(va_list arg, t_printf *node)
{
	unsigned long long	nb;

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
	return (ft_itoa_base(nb, 16));
}

static char		*hexhelper(char *str, int code, t_printf *node)
{
	char	*new;
	int		i;

	if (code == 0)
	{
		new = addchar(str, 0);
		node->hash = 0;
	}
	if (code == 1)
	{
		i = 0;
		while (node->format == 'X' && str[i])
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] = str[i] - 32;
			i++;
		}
		new = ft_strdup(str);
		free(str);
	}
	return (new);
}

static char		*check_edges(char *res, t_printf *node)
{
	if (node->minus && node->zero)
		node->zero = 0;
	if (node->precision && node->dot && node->zero)
		node->zero = 0;
	res = handle_zero(res, node);
	if (node->precision && ((int)ft_strlen(res) < node->precision))
	{
		res = precision(res, node, node->precision);
		if (node->zero)
			node->zero = 0;
	}
	if (node->hash && !node->zero)
		res = hexhelper(res, 0, node);
	return (res);
}

int				print_hex(va_list arg, t_printf *node)
{
	char	*res;
	int		i;

	res = get_arg_hex(arg, node);
	res = check_edges(res, node);
	if (node->width)
	{
		if (!node->zero)
			res = width(res, node, ' ', node->width);
		else
		{
			if (node->hash)
				res = width(res, node, '0', node->width - 2);
			if (node->hash)
				res = hexhelper(res, 0, node);
			else
				res = width(res, node, '0', node->width);
		}
	}
	res = hexhelper(res, 1, node);
	i = 0;
	while (res[i])
		node->printed += write(1, &res[i++], 1);
	free(res);
	return (0);
}
