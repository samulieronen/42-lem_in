/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:30:59 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 14:32:20 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*str_precision(char *str, int len, t_printf *node)
{
	char	*nstr;
	int		del;

	del = 0;
	if (ft_strequ(str, "(null)"))
		del = 1;
	if (len < node->precision || !node->dot)
		nstr = ft_strdup(str);
	else
	{
		if (!(nstr = ft_strndup(str, node->precision)))
			exit(-1);
	}
	if (del == 1)
		free(str);
	return (nstr);
}

int				print_str(va_list arg, t_printf *node)
{
	char	*res;
	int		i;

	res = va_arg(arg, char*);
	if (!res)
		res = ft_strdup("(null)");
	res = str_precision(res, ft_strlen(res), node);
	i = 0;
	if (node->width && node->width > (int)ft_strlen(res))
		res = width(res, node, ' ', node->width);
	while (res[i])
		node->printed += write(1, &res[i++], 1);
	free(res);
	return (0);
}
