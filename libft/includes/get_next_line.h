/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:35:53 by seronen           #+#    #+#             */
/*   Updated: 2020/10/14 16:53:51 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 5
# define MAX_FD 8194
# include "libft.h"

int		get_next_line(const int fd, char **line);

#endif
