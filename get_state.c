/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:05:59 by albaud            #+#    #+#             */
/*   Updated: 2023/03/02 02:29:43 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	dist(int x, int y, int x1, int y1)
{
	return (sqrt(pow(x - x1, 2) + pow(y - y1, 2)));
}

double	neightbors(t_game *s, int x, int y)
{
	double	res;

	res = 1.0;
	if (x + 1 < 4)
		res += s->board.arr[x + 1].arr[y];
	if (x - 1 > -1)
		res += s->board.arr[x - 1].arr[y];
	if (y + 1 < 4)
		res += s->board.arr[x].arr[y + 1];
	if (y - 1 > -1)
		res += s->board.arr[x].arr[y - 1];
	return (res);
}

int	fitness(t_game *s)
{
	int	i;
	int	j;
	int	f;

	i = -1;
	f = 0;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			f += (int)(pow(2, s->board.arr[i].arr[j])
					* (fabs((double)i - 1.5) + 1)
					* (fabs((double)j - 1.5) + 1));
		}
	}
	if (f <= 0)
	{
		error("omg");
	}
	return (f);
}

void	get_state(t_game *s, t_v *state)
{
	int	i;
	int	j;

	v_clear(state, 0);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			state->arr[i * 4 + j] = s->board.arr[i].arr[j];
		}
	}
}

void	get_stats(t_game *s, t_v *state)
{
	int	i;
	int	j;

	v_clear(state, 0);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			state->arr[12 * (i * 4 + j) + (int)s->board.arr[i].arr[j]] = 1;
		}
	}
}
