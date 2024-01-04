/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:29:18 by albaud            #+#    #+#             */
/*   Updated: 2023/03/02 19:04:26 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	save_board(t_game *g)
{
	unsigned long	res;
	int				x;
	int				y;

	res = 0;
	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
		{
			res = res << 4;
			res += (int)g->board.arr[x].arr[y];
		}
	}
	return (res);
}

void	loard_board(t_game *g, unsigned long b)
{
	int				x;
	int				y;
	double			e;

	e = (double)(b & 15);
	x = 4;
	while (--x >= 0)
	{
		y = 4;
		while (--y >= 0)
		{
			g->board.arr[x].arr[y] = (double)(b & 15);
			b = b >> 4;
		}
	}
}

int	test_best(t_game *g, int depth);
int	maximise(t_game *g, int move, int depth)
{
	int				max;
	int				i;
	// int				t;
	unsigned long	b;
	// t_v3			kk;

	if (depth <= 0)
		return (fitness(g));
	max = -9999999;
	b = save_board(g);
	i = step(g, move);
	if (i == 0)
		return (fitness(g));
	i = -1;
	test_best(g, depth);
	loard_board(g, b);
	return (max);
}

int	test_best(t_game *g, int depth)
{
	int	x;
	int	y;
	int	c;
	int	i;
	int	max;
	int	t;

	i = -1;
	max = -1;
	while (++i < 4)
	{
		c = 0;
		x = -1;
		while (++x < 4)
		{
			y = -1;
			t = 0;
			while (++y < 4)
			{
				if (g->board.arr[x].arr[y] == 0)
				{
					g->board.arr[x].arr[y] = 1.0;
					t += maximise(g, i, depth - 1);
					g->board.arr[x].arr[y] = 0;
					c++;
				}
			}
		}
		if (t > max)
			max = t;
	}
	return ((double)max / c);
}

int	max_max(t_game *g, int depth)
{
	int		max;
	int		ind;
	int		i;
	int		t;

	ind = 0;
	max = -9999999;
	i = -1;
	while (++i < 4)
	{
		t = maximise(g, i, depth);
		if (t > max)
		{
			max = t;
			ind = i;
		}
	}
	return (ind);
}
