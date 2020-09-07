/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_ccount.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:45:00 by seronen           #+#    #+#             */
/*   Updated: 2019/10/31 16:45:29 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_word_ccount(char *str, char c)
{
	int i;
	int word;

	i = 0;
	word = 0;
	if (!str && str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c && i > 0 && str[i - 1] != c)
			word++;
		i++;
	}
	word++;
	if (i > 0 && str[i - 1] == c)
		word--;
	return (word);
}
