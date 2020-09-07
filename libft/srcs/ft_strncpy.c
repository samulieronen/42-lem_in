/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:23:29 by seronen           #+#    #+#             */
/*   Updated: 2019/10/29 17:16:05 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t			i;
	unsigned char	*src1;

	src1 = (unsigned char*)src;
	i = 0;
	while (src1[i] != '\0' && i < len)
	{
		dest[i] = src1[i];
		i++;
	}
	while (i < len)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
