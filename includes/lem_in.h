/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:53:03 by seronen           #+#    #+#             */
/*   Updated: 2020/10/28 16:48:01 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>		// remove

// 0 don't, 1 yaaas

#define PRINT_PATHS 0

// 1 for max flow algo, 0 for standard DFS

#define FINDER 1

// Print the input = 1 ON (DEFAULT), 0 OFF

#define PRINT_IN 0

// Print total nb of moves = 0 for NO, 1 for YES

#define PRINT_MV 1

#define SUPER 0

#define TABLE_SIZE	2099
#define MAX_KEY		30

typedef struct	s_pipe				//	Struct to store all the connections from the rooms as one room can have n connections
{
	int				cap;
	int				flow;
	struct s_room	*room;
	struct s_pipe	*adj;
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
	int				hash;

	int				visited;		//	Mark for a visited room
	int				mapped;
	int				flag;

	t_pipe			*pipes;
	struct s_room	*next;
}				t_room;

typedef struct	s_path
{
	struct s_room *r;
	struct s_path *next;
}				t_path;

typedef	struct	s_pathf
{
//	char			*path;
	int				*id_arr;
	int				len;
	float				res;
	t_path			*path;
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
//	int				**setarr;
	int				index;
	int				amount;
	int				steps_total;
	int				max_moves;
	t_pathf			*paths;
	struct s_set	*next;
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

typedef struct	s_queue
{
	struct s_room	*room;
	struct s_queue	*next;
}				t_queue;

typedef struct	s_parent
{
	struct s_room	*from;
	struct s_room	*room;
//	struct t_pipe	*used;
	struct s_parent	*next;
	struct s_parent *prev;
}				t_parent;

typedef struct	s_lemin				//	Main struct
{
	long long		antcount;		//	Should be selfexplanatory
	int				roomnb;
	int				mod;
	int				pathcount;
	int				v_token;
	int				m_token;

	t_room			*start;
	t_room			*end;

	t_hash			*hash[TABLE_SIZE];

	t_map			*map;
	t_ant			*ants;
	t_room			*rooms;
	t_pathf			*pathf;
	t_set			*sets;
}				t_lemin;


int			get_input(t_lemin *node);
int     	make_ants(t_lemin *node);
void		ft_error(char *msg);
char		*get_paths(t_lemin *node);
int			path_len(t_pathf *head);




// EXPERIMENTAL

int     super_algo(t_lemin *node);


// CALC.C

int		calc(t_lemin *node);


// SETS.C

int				manage_sets(t_lemin *node, t_pathf *p);


// PATHFINDING.C

int			pathfinding(t_lemin *node, t_room *head,int *p, int len);


// FLOW.C & PATH.C

int			solve(t_lemin *node);
int			graph_path(t_lemin *node, t_queue *q, t_set *s, int *flow);
t_queue		*q_del(t_queue *q);
int			q_check(t_lemin *node, t_queue *q, t_room *r);
int			q_add(t_queue **q, t_room *new);
int			q_visit(t_lemin *node, t_queue *q);
int			q_parent(t_parent *p, t_room *r);
t_parent	*init_parent(t_room *r);


// PATHCHOOSERS

int			pathchoosing(t_lemin *node);
int			pathchooser(t_lemin *node, t_map *map);
int			pathchooser2(t_lemin *node, t_map *map);


// ROOMS.C

int		build_room(t_lemin *node, char *line);


// PIPES.C

int		build_pipes(t_lemin *node, char *line, int rev);


// HASH.C / HASH_UTILS.C

void			insert_hash(t_lemin *node, char *key, t_room *room);
void			*fetch_hash(t_hash **table, char *key);

void			hashadd(t_hash **alst, t_hash *new);
t_hash			*hashnew(char **key, t_room **room);

#endif