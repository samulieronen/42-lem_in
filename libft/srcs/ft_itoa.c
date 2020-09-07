/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 11:47:30 by seronen           #+#    #+#             */
/*   Updated: 2019/10/29 16:11:25 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	char	*ascii;
	int		len;
	long	nb;

	nb = n;
	len = ft_number_len(n);
	if (!(ascii = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n < 0)
	{
		nb = nb * -1;
		ascii[0] = '-';
	}
	ascii[len] = '\0';
	len--;
	while (nb > 9)
	{
		ascii[len] = (nb % 10 + '0');
		nb = nb / 10;
		len--;
	}
	ascii[len] = (nb % 10 + 48);
	return (ascii);
}
