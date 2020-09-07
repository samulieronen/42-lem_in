/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:19:10 by seronen           #+#    #+#             */
/*   Updated: 2019/10/22 16:25:14 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long i;

	i = n;
	if (i < 0)
	{
		write(fd, "-", 1);
		i = i * -1;
	}
	if (i >= 0 && i < 10)
	{
		ft_putchar_fd(i + 48, fd);
	}
	else if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
		ft_putnbr_fd(i % 10, fd);
	}
}
