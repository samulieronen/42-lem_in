/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:01:42 by seronen           #+#    #+#             */
/*   Updated: 2019/10/29 16:26:30 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned char	*str;
	char			*fresh;
	unsigned int	i;

	str = (unsigned char*)s;
	if (!str)
		return (NULL);
	fresh = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!fresh)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		fresh[i] = f(i, str[i]);
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
