/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:57:00 by seronen           #+#    #+#             */
/*   Updated: 2020/02/26 13:22:38 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	round_ftoa(int precision)
{
	long double	round;
	int			max;

	round = 0.5;
	max = 0;
	while (max++ < precision)
	{
		round /= 10.0;
	}
	return (round);
}

static char		*get_decimals(char *dest, long double f, int prec)
{
	unsigned long long	nb;
	int					i;
	int					resprec;

	i = 1;
	nb = 0;
	resprec = prec;
	while (prec-- > 0)
	{
		f *= 10.0;
		nb = f;
		f -= nb;
		dest[i++] = nb + '0';
	}
	if (resprec > 18 && (f * 10) > 5)
		dest[i - 1]++;
	return (dest);
}

char			*ft_ftoa(long double f, int precision)
{
	unsigned long long	nb;
	char				*ipart;
	char				*fpart;
	char				*res;

	f = f + round_ftoa(precision);
	nb = f;
	ipart = ft_itoa_base(nb, 10);
	f = f - nb;
	if (precision == 0)
		return (ipart);
	fpart = ft_strnew(precision + 2);
	fpart[0] = '.';
	fpart = get_decimals(fpart, f, precision);
	res = ft_strjoin(ipart, fpart);
	free(ipart);
	free(fpart);
	return (res);
}
