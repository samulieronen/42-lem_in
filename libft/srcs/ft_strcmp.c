/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:08:58 by seronen           #+#    #+#             */
/*   Updated: 2020/02/20 13:44:35 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (str1[i] == str2[i])
	{
		i++;
		if (str1[i] == '\0' || str2[i] == '\0')
			break ;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	else
		return (str1[i] - str2[i]);
}
