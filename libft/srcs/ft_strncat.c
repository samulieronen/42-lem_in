/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:28:41 by seronen           #+#    #+#             */
/*   Updated: 2019/10/25 15:13:44 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (!s1 && !s2)
		return (0);
	if (s2[0] == '\0')
		return (s1);
	while (s1[i] != '\0')
		i++;
	while (s2[k] != '\0' && k < n)
	{
		s1[i + k] = s2[k];
		k++;
	}
	s1[i + k] = '\0';
	return (s1);
}
