/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:32:42 by seronen           #+#    #+#             */
/*   Updated: 2020/02/06 13:48:20 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t len)
{
	size_t	i;
	char	*newstring;
	char	*src;

	i = 0;
	src = (char*)str;
	if (!(newstring = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (src[i] != '\0' && len > 0)
	{
		newstring[i] = src[i];
		i++;
		len--;
	}
	newstring[i] = '\0';
	return (newstring);
}
