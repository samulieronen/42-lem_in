/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:16:11 by seronen           #+#    #+#             */
/*   Updated: 2019/10/25 15:11:56 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
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
			while (needle[k] && haystack[i + k] == needle[k] && (i + k) < n)
				k++;
			if (needle[k] == '\0')
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
