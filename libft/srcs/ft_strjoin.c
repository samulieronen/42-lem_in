/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:45:30 by seronen           #+#    #+#             */
/*   Updated: 2019/11/03 12:56:57 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		k;

	if (!s2 && !s1)
		return (NULL);
	str = (char*)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		str[k] = s1[i];
		i++;
		k++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[k + i] = s2[i];
		i++;
	}
	str[k + i] = '\0';
	return (str);
}
