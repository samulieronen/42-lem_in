/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:37:25 by seronen           #+#    #+#             */
/*   Updated: 2019/10/28 16:03:54 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*fresh;

	i = 0;
	fresh = (char*)malloc(sizeof(char) * (size + 1));
	if (!fresh)
		return (NULL);
	while (i < size)
	{
		fresh[i] = '\0';
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
