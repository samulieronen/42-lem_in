/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:52:21 by seronen           #+#    #+#             */
/*   Updated: 2020/02/24 14:28:33 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*precision(char *str, t_printf *node, int nb)
{
	char	*new;
	char	*res;

	nb = nb - ft_strlen(str);
	new = strnew_char(nb, '0');
	res = ft_strjoin(new, str);
	free(new);
	free(str);
	if (node->plus)
		return (res);
	return (res);
}

static char		*addmark(char *str, char mark, t_printf *node)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	new = ft_strnew(ft_strlen(str) + 2);
	while (str[i] && str[i] == ' ')
		new[k++] = str[i++];
	if (str[i] == '\0' && node->minus)
	{
		new[0] = mark;
		i--;
	}
	else
		new[k++] = mark;
	while (str[i])
	{
		new[k] = str[i];
		i++;
		k++;
	}
	return (new);
}

char			*manage_plus_minus(t_printf *node, char *str)
{
	char	mark;
	char	*tmp;

	if (node->sign == 2)
		mark = '+';
	else if (node->sign == 1)
		mark = '-';
	else
		return (str);
	if (!node->width)
	{
		tmp = (char*)malloc(sizeof(char) * ft_strlen(str) + 2);
		tmp[0] = (char)mark;
		ft_strcpy(&tmp[1], str);
	}
	else
		tmp = addmark(str, mark, node);
	free(str);
	return (tmp);
}

char			*handle_space(t_printf *node, char *str)
{
	char *tmp;

	if (!node->space || node->sign || node->plus)
		return (str);
	if (!node->width)
	{
		str = addchar(str, ' ');
	}
	else if (!node->minus)
	{
		str[0] = (char)' ';
	}
	else if (node->minus)
	{
		str = addchar(str, ' ');
		tmp = ft_strndup(str, ft_strlen(str) - 1);
		free(str);
		str = tmp;
	}
	return (str);
}

char			*width(char *str, t_printf *node, char c, int nb)
{
	char	*new;
	char	*res;

	if ((int)ft_strlen(str) >= node->width)
	{
		node->width = 0;
		node->minus = 0;
		return (str);
	}
	if (node->plus && node->sign == 2)
		nb += 1;
	nb = nb - ft_strlen(str);
	new = strnew_char(nb, c);
	if (node->minus)
		res = ft_strjoin(str, new);
	else
		res = ft_strjoin(new, str);
	free(new);
	free(str);
	return (res);
}
