/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:00:51 by albaud            #+#    #+#             */
/*   Updated: 2023/03/01 16:01:05 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

# define HEADER_H

# define BEST 10

# define POPSIZE 1000

# define DATASIZE 60000
# define INPUT 16
# define OUTPUT 4
# define HIDEN 2
# define ITERATION 100
# define PSIZE 200

# include "koflibc/sources.h"
# include "p/p.h"
# include "cfiles/cfiles.h"
# include "libia/libia.h"

typedef struct s_move
{
	struct s_move	*next;
	t_v				*input;
	t_v				*output;
	double			value;
}	t_move;

typedef struct s_run
{
	t_move	*head;
	t_move	*tail;
	int		size;
	int		score;
	int		m;
}	t_run;

typedef struct s_body
{
	struct s_body	*next;
	int				x;
	int				y;
}	t_body;

typedef struct s_snake
{
	t_body	*head;
	t_body	*tail;
	int		size;
	int		dir;
}	t_snake;

typedef struct s_game
{
	t_mtx		board;
	t_canvas	piece[12];
	t_window	w;
	int			x;
	int			y;
	t_net		net;
	t_vis		vis;
	int			play;
	t_mtx		free;
}	t_game;

int		max_max(t_game *g, int depth);
int		fitness(t_game *s);
void	free_move(t_run	*run);
double	dist(int x, int y, int x1, int y1);
void	free_runs(t_run *runs);
void	add_move(t_run *r, int move, t_v *state, double v);
void	reset_game(t_game *g);
void	error(char *n);
void	init_game(t_game *g, int x, int y);
int		step(t_game *s, int action);
void	draw_board(t_game *game);
int		win(t_game *g);
int		key_mmove(int k, t_game *s);
void	add_body(t_snake *s, int x, int y);

void	train(t_game *game, int generations, int r);
t_run	neuron_game(t_game *g);
void	get_state(t_game *s, t_v *state);

#endif