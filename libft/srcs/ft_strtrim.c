/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:18:52 by seronen           #+#    #+#             */
/*   Updated: 2019/11/05 09:41:38 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_frontwhite(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

static size_t		ft_endwhite(const char *s)
{
	size_t l;
	size_t num;

	l = ft_strlen(s);
	l--;
	num = 0;
	while (s[l] == ' ' || s[l] == '\n' || s[l] == '\t')
	{
		l--;
		num++;
	}
	return (num);
}

static char			*ft_fullblank(void)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * 1);
	str[0] = '\0';
	return (str);
}

char				*ft_strtrim(const char *s)
{
	size_t		i;
	size_t		k;
	size_t		st;
	size_t		e;
	char		*fresh;

	i = 0;
	k = 0;
	st = ft_frontwhite(s);
	e = ft_endwhite(s);
	if (ft_strlen(s) == st)
	{
		fresh = ft_fullblank();
		return (fresh);
	}
	if (!(fresh = (char*)malloc(sizeof(char) * (ft_strlen(s) - (e + st) + 1))))
		return (NULL);
	while (st < (ft_strlen(s) - e))
	{
		fresh[k] = s[st];
		k++;
		st++;
	}
	fresh[k] = '\0';
	return (fresh);
}
