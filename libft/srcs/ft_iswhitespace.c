/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:41:48 by seronen           #+#    #+#             */
/*   Updated: 2020/11/01 21:43:17 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int     ft_iswhitespace(int c)
{
    if (c == '\t' || c == ' ')
        return (1);
    return (0);
}