/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:08:58 by seronen           #+#    #+#             */
/*   Updated: 2019/10/29 13:19:12 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t len)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 0;
	if (len == 0)
		return (0);
	while (str1[i] == str2[i] && i < len - 1)
	{
		if (str1[i] == '\0' || str2[i] == '\0')
			break ;
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	else
		return (str1[i] - str2[i]);
}
