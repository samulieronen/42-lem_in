/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 03:21:07 by seronen           #+#    #+#             */
/*   Updated: 2020/11/04 14:44:52 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcdup(const char *s1, char c)
{
	size_t	i;
	char	*newstring;
	char	*src;

	i = 0;
	if (!s1)
		return (NULL);
	src = (char*)s1;
	newstring = (char*)malloc(sizeof(char) * (ft_word_len_ic(src, c) + 1));
	if (!newstring)
		return (NULL);
	while (src[i] != '\0' && src[i] != c)
	{
		newstring[i] = src[i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
