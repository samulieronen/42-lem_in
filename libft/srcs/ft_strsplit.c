/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:34:59 by seronen           #+#    #+#             */
/*   Updated: 2019/11/14 14:25:28 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				**ft_strsplit(const char *s, char c)
{
	char	**fresh;
	char	*str;
	int		i;
	int		j;
	int		len;

	str = (char*)s;
	i = 0;
	j = 0;
	if (!(fresh = (char**)malloc(sizeof(char*) * (ft_word_ccount(str, c) + 1))))
		return (NULL);
	while (j < ft_word_ccount(str, c))
	{
		while (str[i] == c)
			i++;
		len = ft_word_len_ic(&str[i], c);
		if (!(fresh[j] = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		fresh[j] = ft_strncpy(fresh[j], &str[i], len);
		fresh[j][len] = '\0';
		j++;
		i = i + len;
	}
	fresh[j] = NULL;
	return (fresh);
}
