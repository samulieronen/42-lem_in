/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:48:54 by seronen           #+#    #+#             */
/*   Updated: 2019/10/28 16:14:32 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	int		i;
	char	*str;
	char	*fresh;

	i = 0;
	if (!s)
		return (NULL);
	str = (char*)s;
	fresh = (char*)malloc(sizeof(char) * (ft_strlen(str)) + 1);
	if (!fresh)
		return (NULL);
	while (str[i] != '\0')
	{
		fresh[i] = f(str[i]);
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
