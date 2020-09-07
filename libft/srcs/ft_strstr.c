/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:26:50 by seronen           #+#    #+#             */
/*   Updated: 2019/10/25 15:11:06 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (!*needle)
		return ((char*)haystack);
	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			k = 1;
			while (needle[k] != '\0' && haystack[i + k] == needle[k])
				k++;
			if (needle[k] == '\0')
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
