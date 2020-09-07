/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_len_ic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:45:47 by seronen           #+#    #+#             */
/*   Updated: 2019/11/20 15:55:57 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_word_len_ic(char *str, char c)
{
	int i;
	int flaw;

	i = 0;
	flaw = 0;
	while (str[i] == c)
	{
		i++;
		flaw++;
	}
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i - flaw);
}
