/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_ia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:34:25 by albaud            #+#    #+#             */
/*   Updated: 2023/02/27 10:18:03 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_run	random_game(t_game *g)
{
	int		r;
	t_run	res;
	t_v		inp;
	int		st;
	int		m;

	inp = v_new(INPUT, 0);
	res.head = 0;
	res.size = 0;
	res.tail = 0;
	res.score = 0;
	m = 0;
	while (1)
	{
		get_state(g, &inp);
		st = (int)rand_range(0, 4);
		r = step(g, st);
		add_move(&res, st, &inp, r);
		m += !r;
		if (r != 0)
			m = 0;
		if (m >= 5)
		{
			res.score = fitness(g);
			res.m = pow(2, (int)m_max(&g->board));
			reset_game(g);
			break ;
		}
	}
	//printf("mmmm %i %i %i\n", res.score, res.size, res.m);
	return (res);
}

t_run	neuron_game(t_game *g)
{
	int		r;
	t_run	res;
	t_v		inp;
	int		st;
	int		m;

	inp = v_new(INPUT, 0);
	res.head = 0;
	res.size = 0;
	res.score = 0;
	m = 0;
	while (1)
	{
		get_state(g, &inp);
		ia_forward(&g->net, &inp);
		st = v_maxi(&g->net.predicted_output);
		r = step(g, st);
		add_move(&res, st, &inp, r);
		if (r == 0 && ++m)
		{
			st = (int)rand_range(0, 4);
			step(g, st);
		}
		else
			m = 0;
		if (m >= 5)
		{
			res.score = fitness(g);
			res.m = pow(2, (int)m_max(&g->board));
			reset_game(g);
			break ;
		}
	}
	//printf("mmmm %i %i %i\n", res.score, res.size, res.m);
	return (res);
}

void	learn(t_game *g, t_run *runs)
{
	t_run	t;
	int		j;
	int		f;
	t_move	*m;
	int		k;

	f = 1;
	while (f)
	{
		f = 0;
		j = -1;
		while (++j < POPSIZE - 1)
		{
			if (runs[j].score < runs[j + 1].score)
			{
				t = runs[j];
				runs[j] = runs[j + 1];
				runs[j + 1] = t;
				f = 1;
			}
		}
	}
	j = -1;
	printf("mmmm %i %i %i\n", runs[0].score, runs[0].size, runs[0].m);
	while (++j < POPSIZE)
	{
		f = rand_range_weight(POPSIZE, 10) / 100;
		m = runs[f].head;
		k = runs[f].size;
		while (m)
		{
			if (m->value)
			{
				ia_forward(&g->net, m->input);
				ia_backward(&g->net, m->input, m->output);
			}
			m = m->next;
		}
	}
}

void	train(t_game *game, int generations, int r)
{
	int		i;
	int		j;
	t_run	population[POPSIZE];
	t_run	children[POPSIZE];
	char	*n;

	(void) n;
	i = -1;
	if (!r)
	{
		while (++i < POPSIZE)
			population[i] = random_game(game);
	}
	else
	{
		while (++i < POPSIZE)
			population[i] = neuron_game(game);
	}
	i = -1;
	while (++i < generations)
	{
		progressbar("generationing :)", i, generations);
		net_clear(&game->net);
		learn(game, population);
		n = ft_itoa(population[0].score);
		ia_save(&game->net, n);
		free(n);
		j = -1;
		while (++j < POPSIZE)
			children[j] = neuron_game(game);
		free_runs(population);
		j = -1;
		while (++j < POPSIZE)
			population[j] = children[j];
	}
	progressbar("generationing :)", i, generations);
}
