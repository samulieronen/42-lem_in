/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:53:03 by seronen           #+#    #+#             */
/*   Updated: 2020/10/17 00:20:47 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <stdio.h>

// 0 value for old pathcooser, 1 for newer one

#define CHOOSER 1

// Print the input = 1 ON (DEFAULT), 0 OFF

#define PRINT_IN 0

// Print total nb of moves = 0 for NO, 1 for YES

#define PRINT_MV 1



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
	int				visited;		//	Mark for a visited room
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
	int					*anttable;
	int					pathset;			// How many paths in set
	int					pathsetlen;			// How long the whole set is
	int					moves;				// How many moves it takes in total
	struct s_pathset	*next;
}				t_pathset;

typedef struct	s_map
{
	t_pathf				*paths;
	long long		max_paths;
	long long		max_moves;
	int				*ant;
	int				*path;
	struct s_map		*next;
}				t_map;


typedef struct	s_lemin				//	Main struct
{
	long long		antcount;		//	Should be selfexplanatory
//	long long		max_paths;
	t_map			*map;
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
int			pathchooser(t_lemin *node, t_map *map);
void		add_path(t_lemin *node, char *path);

#endif