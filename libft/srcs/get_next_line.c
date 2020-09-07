/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:35:39 by seronen           #+#    #+#             */
/*   Updated: 2020/03/03 12:59:00 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	make_line(char **save, int fd, char **line)
{
	int		i;
	char	*fresh;

	i = 0;
	while (save[fd][i] != '\0' && save[fd][i] != '\n')
		++i;
	if (save[fd][i] == '\n')
	{
		*line = ft_strsub(save[fd], 0, i);
		fresh = ft_strdup(&save[fd][i + 1]);
		free(save[fd]);
		save[fd] = fresh;
		if (save[fd][0] == '\0')
			ft_strdel(&save[fd]);
	}
	else if (save[fd][i] == '\0')
	{
		*line = ft_strsub(save[fd], 0, i);
		ft_strdel(&save[fd]);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char		*save[MAX_FD];
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*fresh;

	if (BUFF_SIZE < 1 || fd > MAX_FD || fd < 0 || !line)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (save[fd] == NULL)
			if (!(save[fd] = ft_strnew(0)))
				return (-1);
		if (!(fresh = ft_strjoin(save[fd], buf)))
			return (-1);
		free(save[fd]);
		save[fd] = fresh;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	if (save[fd] == NULL || save[fd][0] == '\0')
		return (0);
	return (make_line(save, fd, line));
}
