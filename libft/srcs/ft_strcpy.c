/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:17:33 by seronen           #+#    #+#             */
/*   Updated: 2019/10/25 15:10:02 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, const char *src)
{
	int		i;
	char	*src1;

	src1 = (char*)src;
	i = 0;
	while (src1[i] != '\0')
	{
		dest[i] = src1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
