/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:56:50 by seronen           #+#    #+#             */
/*   Updated: 2020/09/04 03:22:18 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*newstring;
	char	*src;

	i = 0;
	src = (char*)s1;
	newstring = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!newstring)
		return (NULL);
	while (src[i] != '\0')
	{
		newstring[i] = src[i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
