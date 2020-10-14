/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:53:03 by seronen           #+#    #+#             */
/*   Updated: 2020/10/14 13:47:04 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <stdio.h>

typedef struct	s_pipe				//	Struct to store all the connections from the rooms as one room can have n connections
{
	char			*name;
	struct s_room	*room;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_ant
{
	int				antnb;
	struct s_ant	*next;
}				t_ant;

typedef struct	s_room				//	Struct to store all the rooms as there will be ( > 2 ) rooms
{
	char			*name;			//	Rooms name to identify it from the rest
	char			*info;
	int				paths_used;
	int				visited;		//	Mark for a visited room
	int				dead;
	t_pipe			*pipes;
	struct s_room	*next;
}				t_room;

typedef	struct	s_log
{
	int		start;
	int		end;
	int		modid;					//	Tells our parser which modifier we have in hand, start or end.
}				t_log;

typedef	struct	s_pathf
{
	char	*path;
	int		len;
	struct 	s_pathf *next;
}				t_pathf;

typedef struct	s_pathset
{
	t_pathf				*path;
	int					*movetable;
	int					pathset;			// How many paths in set
	int					pathsetlen;			// How long the whole set is
	int					moves;				// How many moves it takes in total
	struct s_pathset	*next;
}				t_pathset;

typedef struct	s_lemin				//	Main struct
{
	int				antcount;		//	Should be selfexplanatory
	t_ant			*ants;
	t_room			*rooms;
	t_log			*log;
	t_pathf			*pathf;
	t_pathset		*sets;
}				t_lemin;


int			get_input(t_lemin *node);
int     	make_ants(t_lemin *node);
void		ft_error(char *msg);
char		*get_paths(t_lemin *node);
t_room		*fetch_room(t_room *head, char *keyword);
t_room		*fetch_modroom(t_room *head, char *keyword);
t_room      *pathfinding(t_lemin *node, t_room *head, char *path);
int			pathchoosing(t_lemin *node);

#endif