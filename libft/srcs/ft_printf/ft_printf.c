/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:47:05 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 15:56:26 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		get_arg(t_printf *node, va_list arg)
{
	long long nb;

	if (!node->dot)
	{
		nb = va_arg(arg, int);
		if (!nb)
			return (1);
		node->width = nb;
		node->widthst = 1;
	}
	else if (node->dot && !node->precision)
	{
		nb = va_arg(arg, int);
		if (!nb)
			return (1);
		node->precision = nb;
		node->precisionst = 1;
	}
	else
		return (1);
	return (0);
}

static int		save_flag(char flag, t_printf *node, va_list arg)
{
	if (flag == '#')
		node->hash = (int)flag;
	else if (flag == '+')
		node->plus = (int)flag;
	else if (flag == '-')
		node->minus = (int)flag;
	else if (flag == ' ')
		node->space = (int)flag;
	else if (flag == '0' && !node->zero && !node->dot && !node->width)
		node->zero = (int)flag;
	else if (flag == '*')
		get_arg(node, arg);
	else if (flag == '.')
		node->dot = (int)flag;
	else if (ft_strchr("0123456789", flag))
	{
		if (!node->dot)
			save_width(node, flag);
		else
			save_precision(node, flag);
	}
	else if (ft_strchr(LENMOD, flag))
		save_length(flag, node);
	return (0);
}

static int		get_format(char format, va_list arg, t_printf *node)
{
	if (format == 'c')
		print_char(arg, node);
	if (format == 's')
		print_str(arg, node);
	if (format == 'd' || format == 'i')
		print_dec(arg, node);
	if (format == 'p')
		print_ptr(arg, node);
	if (format == 'o')
		print_octal(arg, node);
	if (format == 'u')
		print_unsig(arg, node);
	if (format == 'x' || format == 'X')
		print_hex(arg, node);
	if (format == 'f')
		print_float(arg, node);
	if (format == '%')
		print_percentage(node);
	return (0);
}

int				parser(char *format, va_list arg, t_printf *node)
{
	int i;

	i = 0;
	while (ft_strchr(ALLSYM, format[i]) && format[i])
	{
		if (ft_strchr(FORMAT, format[i]))
		{
			node->format = format[i];
			get_format(format[i], arg, node);
			break ;
		}
		else if (!strchr(FORMAT, format[i]))
		{
			save_flag(format[i], node, arg);
		}
		i++;
	}
	if (!strchr(ALLSYM, format[i]))
		exit(-1);
	return (i);
}

int				ft_printf(const char *format, ...)
{
	t_printf	*node;
	va_list		arg;
	char		*s;
	int			i;

	va_start(arg, format);
	s = (char*)format;
	i = 0;
	node = init_node_start();
	while (s[i] && i < (int)ft_strlen(format))
	{
		init_node(node);
		if (s[i] == '%' && s[i + 1] != '\0')
			i = i + (parser(&s[i + 1], arg, node)) + 1;
		else
			node->printed += write(1, &s[i], 1);
		free(node->length);
		i++;
	}
	free(node);
	va_end(arg);
	return (node->printed);
}
