/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:53:03 by seronen           #+#    #+#             */
/*   Updated: 2020/10/30 16:58:17 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>		// remove


# define RED "\033[0;31m"
# define RESET "\033[0m"


// 0 don't, 1 yaaas

#define PRINT_PATHS 0

// 1 for max flow algo, 0 for standard DFS

#define FINDER 1

// Print the input = 1 ON (DEFAULT), 0 OFF

#define PRINT_IN 0

// Print total nb of moves = 0 for NO, 1 for YES

#define PRINT_MV 1

#define SUPER 0
#define LEAKS 0

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
	int				*id_arr;
	int				len;
	double			res;
	t_path			*path;
	struct 	s_pathf *next;
}				t_pathf;

typedef struct	s_set
{
	int				id;
	int				amount;
	int				steps_total;
	double			cost;
	long long		max_moves;
	t_pathf			*paths;
	struct s_set	*next;
}				t_set;

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

	int				line_nb;

	t_room			*start;
	t_room			*end;

	t_hash			*hash[TABLE_SIZE];

	int				antnbr;
	int				steps;
	int				goaled;
	int				set_id;
	t_set			*best;

	t_ant			*ants;
	t_room			*rooms;
	t_pathf			*pathf;
	t_set			*sets;
	t_parent		*parent;
}				t_lemin;


/*
**	PROTOTYPES	– ORGANIZED BY FILE
*/


// EXPERIMENTAL

int     super_algo(t_lemin *node);


// LEM_IN.C

void		ft_error(char *msg);
void		ft_input_error(char *msg, char *s1, int lnbr);


// ANTS.C

int     	make_ants(t_lemin *node);


// INPUT.C

int			get_input(t_lemin *node);


// CALC.C

int		gather_data(t_lemin *node, t_set *set);
int		calc(t_lemin *node, t_set *s);
int		choose_set(t_lemin *node, t_set *s);


// SETS.C

int			add_path(t_path **alst, t_path *new);
t_path		*pathnew(t_lemin *node, t_room *r);
int			path_to_set(t_path *head, t_pathf **alst, int len);
int			*new_set(t_set **alst);
int			free_path(t_path **alst);


// PATHFINDING.C

int			pathfinding(t_lemin *node, t_room *head,int *p, int len);


// FLOW.C & PATH.C

int			solve(t_lemin *node);
int			graph_path(t_lemin *node, t_queue *q, t_set *s);


// QUEUE.C

int			q_add(t_queue **q, t_room *new);
int			q_visit(t_lemin *node, t_queue *q);
t_queue		*q_del(t_queue *q);
int			q_check(t_lemin *node, t_queue *q, t_room *r);
void		q_free(t_queue **alst);


// PARENT.C

t_parent	*parentnew(void);
t_parent	*init_parent(t_lemin *node, t_room *r);
int			q_parent(t_parent *p, t_pipe *pipe);
t_parent	*fetch_parent(t_parent *head, t_room *key);
void		free_parent(t_lemin *node, t_parent **alst);


// PRINT.C

int		print_inception(t_lemin *node, t_set *set);


// PATHCHOOSERS

//int			pathchoosing(t_lemin *node);
//int			pathchooser(t_lemin *node, t_map *map);
//int			pathchooser2(t_lemin *node, t_map *map);


// ROOMS.C

int		build_room(t_lemin *node, char *line);


// PIPES.C

int		build_pipes(t_lemin *node, char *line);


// HASH.C / HASH_UTILS.C

void			insert_hash(t_lemin *node, char *key, t_room *room);
void			*fetch_hash(t_hash **table, char *key);

void			hashadd(t_hash **alst, t_hash *new);
t_hash			*hashnew(char **key, t_room **room);

#endif