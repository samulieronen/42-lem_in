/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:52:07 by seronen           #+#    #+#             */
/*   Updated: 2019/10/28 17:19:21 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	s1 = (unsigned char*)dst;
	s2 = (unsigned char*)src;
	i = 0;
	if (s2 < s1)
	{
		while (len--)
			s1[len] = s2[len];
	}
	else
	{
		while (i < len)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	return (s1);
}
