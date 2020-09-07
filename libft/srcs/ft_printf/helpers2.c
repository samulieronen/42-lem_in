/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:11:58 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 14:08:07 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*strnew_char(size_t nb, char c)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char*)malloc(sizeof(char) * nb + 1);
	while (i < nb)
		new[i++] = c;
	new[i] = '\0';
	return (new);
}

char		*addchar(char *str, char c)
{
	char	*tmp;
	char	*cs;

	if (c == 0)
	{
		cs = ft_strnew(2);
		cs[0] = '0';
		cs[1] = 'x';
	}
	else
	{
		cs = ft_strnew(1);
		cs[0] = c;
	}
	tmp = ft_strjoin(cs, str);
	free(str);
	free(cs);
	return (tmp);
}

int			init_node(t_printf *node)
{
	node->precision = 0;
	node->width = 0;
	node->precisionst = 0;
	node->widthst = 0;
	node->dot = 0;
	node->format = 0;
	node->hash = 0;
	node->minus = 0;
	node->plus = 0;
	node->space = 0;
	node->star = 0;
	node->zero = 0;
	node->sign = 0;
	node->fprecision = 0;
	node->length = NULL;
	return (0);
}

t_printf	*init_node_start(void)
{
	t_printf *node;

	if (!(node = (t_printf*)malloc(sizeof(t_printf))))
		exit(-1);
	node->printed = 0;
	return (node);
}
