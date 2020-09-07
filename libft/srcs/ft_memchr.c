/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:07:03 by seronen           #+#    #+#             */
/*   Updated: 2019/10/28 17:12:00 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	let;

	i = 0;
	let = (unsigned char)c;
	s1 = (unsigned char*)s;
	while (i < n)
	{
		if (s1[i] == let)
			return (&s1[i]);
		i++;
	}
	return (NULL);
}
