/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:53:03 by seronen           #+#    #+#             */
/*   Updated: 2020/10/20 18:01:16 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>		// remove

// 0 value for old pathcooser, 1 for newer one

#define CHOOSER 1

// Print the input = 1 ON (DEFAULT), 0 OFF

#define PRINT_IN 0

// Print total nb of moves = 0 for NO, 1 for YES

#define PRINT_MV 1

// Use names to save path VS ID:s (DEBUG)(CHOOSER MUST BE 1)

#define PATH_SAVE 1


#define TABLE_SIZE	2048
#define MAX_KEY		30

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
	long long		id;
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
	int		*id_arr;
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

typedef struct	s_set
{
	int				*head;
	struct t_set	*next;
}				t_set;

typedef struct	s_map
{
	t_pathf				*paths;
	t_set				*sets;
	long long			max_paths;
	long long			max_moves;
	int					*ant;
	long long			calc;
	struct s_map		*next;
}				t_map;

typedef struct	s_hash
{
	char			*key;
	struct s_room	*room;
	struct s_hash	*next;
}				t_hash;

typedef struct	s_lemin				//	Main struct
{
	long long		antcount;		//	Should be selfexplanatory
	long long		roomnb;

	t_room			*start;
	t_room			*end;

	t_hash			*hash[TABLE_SIZE];

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
int			pathchooser2(t_lemin *node, t_map *map);

void		add_path(t_lemin *node, char *path);

int		path_len(t_pathf *head);

void	insert_hash(t_lemin *node, char *key, t_room *room);
void	init_hash(t_lemin *node);
void	hashadd(t_hash **alst, t_hash *new);
void			*fetch_hash(t_lemin *node, char *key);

#endif