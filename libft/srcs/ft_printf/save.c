/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:09:36 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 13:27:59 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			save_length(char flag, t_printf *node)
{
	char	*new;
	char	*tmp;

	if (!node->length)
		node->length = ft_strnew(0);
	new = ft_strnew(1);
	new[0] = flag;
	tmp = ft_strjoin(new, node->length);
	free(new);
	free(node->length);
	node->length = tmp;
	return (0);
}

static int	save_num(char *target, char *str, char flag, size_t len)
{
	int		res;

	if (!target)
	{
		str[0] = (char)flag;
		str[1] = '\0';
		res = ft_atoi(str);
		free(str);
	}
	else
	{
		ft_strncpy(target, str, len);
		free(str);
		target[len] = (char)flag;
		target[len + 1] = '\0';
		res = atoi(target);
		free(target);
	}
	return (res);
}

int			save_precision(t_printf *node, char flag)
{
	char	*str;
	char	*nstr;
	int		len;
	int		res;

	if (node->precisionst)
	{
		node->precision = 0;
		node->precisionst = 0;
	}
	if (!node->precision)
	{
		str = (char*)malloc(sizeof(char) * 2);
		res = save_num(NULL, str, flag, 0);
		node->precision = res;
	}
	else
	{
		str = ft_itoa(node->precision);
		len = ft_strlen(str);
		nstr = (char*)malloc(sizeof(char) * len + 1);
		res = save_num(nstr, str, flag, len);
		node->precision = res;
	}
	return (0);
}

int			save_width(t_printf *node, char flag)
{
	char	*str;
	char	*nstr;
	int		len;
	int		res;

	if (node->widthst)
	{
		node->width = 0;
		node->widthst = 0;
	}
	if (!node->width)
	{
		str = (char*)malloc(sizeof(char) * 2);
		res = save_num(NULL, str, flag, 1);
		node->width = res;
	}
	else
	{
		str = ft_itoa(node->width);
		len = ft_strlen(str);
		nstr = (char*)malloc(sizeof(char) * len + 1);
		res = save_num(nstr, str, flag, len);
		node->width = res;
	}
	return (0);
}
