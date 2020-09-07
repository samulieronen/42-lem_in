/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:45:14 by seronen           #+#    #+#             */
/*   Updated: 2019/10/25 15:09:42 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s1;

	s1 = (unsigned char*)b;
	i = 0;
	while (i < len)
	{
		s1[i] = c;
		i++;
	}
	return (s1);
}
