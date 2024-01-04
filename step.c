/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:02:42 by albaud            #+#    #+#             */
/*   Updated: 2023/03/02 02:59:01 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	loose(t_game *s, int action)
{

	(void) s;
	(void) action;
	return (0);
}

double	ab(double a)
{
	return (fabs(a));
}

int	ri(t_game *s, int x, int y)
{
	int	f;
	int	t;
	int	m;

	f = x;
	m = 0;
	while (++f < 4)
	{
		t = s->board.arr[f - 1].arr[y];
		s->board.arr[f - 1].arr[y] = 0;
		if (s->board.arr[f].arr[y] == 0 && t && ++m)
			s->board.arr[f].arr[y] = t;
		else if (s->board.arr[f].arr[y] == t && t > 0 && ++m)
			s->board.arr[f].arr[y] = (t + 1) * -1;
		else
			s->board.arr[f - 1].arr[y] = t;
	}
	return (m);
}

int	le(t_game *s, int x, int y)
{
	int	f;
	int	t;
	int	m;

	f = x;
	m = 0;
	while (--f >= 0)
	{
		t = s->board.arr[f + 1].arr[y];
		s->board.arr[f + 1].arr[y] = 0;
		if (s->board.arr[f].arr[y] == 0 && t && ++m)
			s->board.arr[f].arr[y] = t;
		else if (s->board.arr[f].arr[y] == t && t > 0 && ++m)
			s->board.arr[f].arr[y] = (t + 1) * -1;
		else
			s->board.arr[f + 1].arr[y] = t;
	}
	return (m);
}

int	up(t_game *s, int x, int y)
{
	int	f;
	int	t;
	int	m;

	f = y;
	m = 0;
	while (--f >= 0)
	{
		t = s->board.arr[x].arr[f + 1];
		s->board.arr[x].arr[f + 1] = 0;
		if (s->board.arr[x].arr[f] == 0 && t && ++m)
			s->board.arr[x].arr[f] = t;
		else if (s->board.arr[x].arr[f] == t && t > 0 && ++m)
			s->board.arr[x].arr[f] = (t + 1) * -1;
		else
			s->board.arr[x].arr[f + 1] = t;
	}
	return (m);
}

int	down(t_game *s, int x, int y)
{
	int	f;
	int	t;
	int	m;

	f = y;
	m = 0;
	while (++f < 4)
	{
		t = s->board.arr[x].arr[f - 1];
		s->board.arr[x].arr[f - 1] = 0;
		if (s->board.arr[x].arr[f] == 0 && t && ++m)
			s->board.arr[x].arr[f] = t;
		else if (s->board.arr[x].arr[f] == t && t > 0 && ++m)
			s->board.arr[x].arr[f] = (t + 1) * -1;
		else
			s->board.arr[x].arr[f - 1] = t;
	}
	return (m);
}

int	mo(t_game *s, int (*f)(t_game *, int, int), int n)
{
	int	x;
	int	y;
	int	m;

	m = 0;
	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
		{
			if (n)
				m += f(s, x, y);
			else
				m += f(s, 3 - x, 3 - y);
		}
	}
	m_apply(&s->board, ab);
	return (m);
}

void	replace(t_game *s)
{
	int		x;
	int		y;
	int		f;
	int		r;

	f = 0;
	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
		{
			if (s->board.arr[x].arr[y] == 0)
			{
				s->free.arr[f].arr[0] = x;
				s->free.arr[f++].arr[1] = y;
			}
		}
	}
	r = (int)rand_range(0, f);
	s->board.arr[(int)s->free.arr[r].arr[0]]
		.arr[(int)s->free.arr[r].arr[1]] = 1;
	if ((int)rand_range(0, 10) == 1)
		s->board.arr[(int)s->free.arr[r].arr[0]]
			.arr[(int)s->free.arr[r].arr[1]] = 2;
}

int	step(t_game *s, int action)
{
	int	m;

	m = 0;
	if (action == 0)
		m = mo(s, ri, 0);
	if (action == 1)
		m = mo(s, down, 0);
	if (action == 2)
		m = mo(s, le, 1);
	if (action == 3)
		m = mo(s, up, 1);
	if (loose(s, action))
		return (-100);
	if (s->play)
	{
		draw_board(s);
		if (m)
			replace(s);
	}
	return (m);
}

