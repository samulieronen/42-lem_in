/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seronen <seronen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:53:03 by seronen           #+#    #+#             */
/*   Updated: 2020/11/03 16:16:14 by seronen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"

/*
**	COLOR DEFS
*/

# define RED	"\033[0;31m"
# define RESET	"\033[0m"

/*
**	PRINT OPTIONS
*/

# define P_PATHS	0
# define P_INPUT	0
# define P_OUTPUT	1
# define P_MOVES	1

/*
**	ERROR DEFS FOR PARSER
*/

# define ALLOW_SPACES		1
# define ALLOW_DUP_ROOMS	0
# define ALLOW_SELF_LINKING	0
# define ALLOW_EMPTY_LINES	1
# define ALLOW_REORDER		0
# define ERROR_COM			0
# define ERROR_L			1

/*
**	CHECK MEM LEAKS
*/

# define LEAKS 0

/*
**	DEFS FOR HASHTABLE
*/

# define TABLE_SIZE	2099
# define MAX_KEY	30

/*
**	DEF FOR INPUT ARRAY
*/

# define MAX_SIZE	10000

typedef struct	s_pipe
{
	int				cap;
	int				flow;
	struct s_room	*room;
	struct s_pipe	*adj;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_room
{
	long long		id;
	char			*name;
	char			*info;
	int				hash;

	int				visited;
	int				mapped;
	int				flag;

	t_pipe			*pipes;
	struct s_room	*next;
}				t_room;

typedef struct	s_path
{
	struct s_room	*r;
	struct s_path	*next;
}				t_path;

typedef	struct	s_pathf
{
	int				*id_arr;
	int				len;
	int				res;
	t_path			*path;
	struct s_pathf	*next;
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

typedef	struct	s_input
{
	char			*line[MAX_SIZE];
	int				index;
	struct s_input	*next;
}				t_input;

typedef struct	s_lemin
{
	long long		antcount;
	int				roomnb;
	int				mod;
	int				pathcount;
	int				v_token;
	int				m_token;

	int				lnb;
	int				l_check;
	int				r_check;
	t_input			*input;

	t_room			*start;
	t_room			*end;

	t_hash			*hash[TABLE_SIZE];

	int				antnbr;
	int				steps;
	int				goaled;
	int				set_id;
	t_set			*best;

	t_room			*rooms;
	t_set			*sets;
	t_parent		*parent;
}				t_lemin;

/*
**	PROTOTYPES	– ORGANIZED BY FILE
*/

/*
**	LEMIN.C
*/

void			ft_error(char *msg, char *s1, int lnbr);

/*
**	INPUT.C
*/

int				get_input(t_lemin *node);

/*
**	VALIDATE.C
*/

void			validate_ants(t_lemin *node, char *line);
void			validate_room(t_lemin *node, char *line);

/*
**	LINES.C
*/

int				save_input(t_lemin *node, char *line);
void			print_lines(t_lemin *node);

/*
**	CALC.C
*/

int				gather_data(t_lemin *node, t_set *set);
int				calc(t_lemin *node, t_set *s);
int				choose_set(t_lemin *node, t_set *s);

/*
**	SETS.C
*/

int				add_path(t_path **alst, t_path *new);
t_path			*pathnew(t_lemin *node, t_room *r);
int				path_to_set(t_path *head, t_pathf **alst, int len);
int				*new_set(t_set **alst);
int				free_path(t_path **alst);

/*
**	FLOW.C & FLOW_UTILS.C
*/

int				solve(t_lemin *node);
int				ensure_flow(t_lemin *node, t_room *r);
int				calc_flow(t_room *where, t_room *to);
t_pipe			*get_last(t_parent *prev, t_room *to);
int				get_residual(t_lemin *n, t_queue *q, t_parent *p, t_pipe *pr);

/*
**	PATH.C
*/

int				graph_path(t_lemin *node, t_queue *q, t_set *s);

/*
**	QUEUE.C
*/

int				q_add(t_queue **q, t_room *new, t_parent *par, t_pipe *p);
int				q_visit(t_lemin *node, t_queue *q);
t_queue			*q_del(t_queue *q);
int				q_check(t_lemin *node, t_queue *q, t_room *r);
void			q_free(t_queue **alst);

/*
**	PARENT.C
*/

t_parent		*parentnew(void);
t_parent		*init_parent(t_lemin *node, t_room *r);
int				q_parent(t_parent *p, t_pipe *pipe);
t_parent		*fetch_parent(t_parent *head, t_room *key);
void			free_parent(t_lemin *node, t_parent **alst);

/*
**	PRINT.C & PRINT_UTILS.C
*/

int				print_output(t_lemin *node, t_set *set);
int				init_print(t_lemin *node, t_pathf *paths);
int				get_antnbr(t_lemin *node);

/*
**	ROOMS.C
*/

int				build_room(t_lemin *node, char *line);

/*
**	PIPES.C
*/

int				build_pipes(t_lemin *node, char *line);

/*
**	HASH.C & HASH_UTILS.C
*/

void			insert_hash(t_lemin *node, char *key, t_room *room);
void			*fetch_hash(t_hash **table, char *key);
void			hashadd(t_hash **alst, t_hash *new);
t_hash			*hashnew(char **key, t_room **room);

#endif
