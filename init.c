/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:11:44 by albaud            #+#    #+#             */
/*   Updated: 2023/03/02 02:56:14 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	destroy_snake(t_snake *snake)
{
	t_body	*b;
	t_body	*t;

	b = snake->head;
	while (b)
	{
		t = b->next;
		free(b);
		b = t;
	}
	snake->size = 0;
	snake->head = 0;
	snake->tail = 0;
	snake->dir = rand_range(0, 4);
}

void	reset_game(t_game *g)
{
	int	x;
	int	y;

	m_clear(&g->board, 0);
	x = (int)rand_range(0, g->x);
	y = (int)rand_range(0, g->y);
	g->board.arr[x].arr[y] = 1;
	draw_board(g);
}

void	init_game(t_game *g, int x, int y)
{
	if (x < 2 || y < 2)
		error("invalid board size");
	ft_mlx_init(&g->w, x * PSIZE, y * PSIZE, "2048");
	mlx_hook(g->w.win, 2, 0, key_mmove, g);
	g->w.cvs = ft_init_canvas(g->w.mlx, x * PSIZE, y * PSIZE);
	g->board = m_new(x, y, 0);
	g->x = x;
	g->y = y;
	g->free = m_new(16, 2, 0);
	g->board.arr[(int)rand_range(0, 4)].arr[(int)rand_range(0, 4)] = 1;
	g->piece[0] = ft_init_image(g->w.mlx, "sprites/0.xpm");
	g->piece[1] = ft_init_image(g->w.mlx, "sprites/1.xpm");
	g->piece[2] = ft_init_image(g->w.mlx, "sprites/2.xpm");
	g->piece[3] = ft_init_image(g->w.mlx, "sprites/3.xpm");
	g->piece[4] = ft_init_image(g->w.mlx, "sprites/4.xpm");
	g->piece[5] = ft_init_image(g->w.mlx, "sprites/5.xpm");
	g->piece[6] = ft_init_image(g->w.mlx, "sprites/6.xpm");
	g->piece[7] = ft_init_image(g->w.mlx, "sprites/7.xpm");
	g->piece[8] = ft_init_image(g->w.mlx, "sprites/8.xpm");
	g->piece[9] = ft_init_image(g->w.mlx, "sprites/9.xpm");
	g->piece[10] = ft_init_image(g->w.mlx, "sprites/10.xpm");
	g->piece[11] = ft_init_image(g->w.mlx, "sprites/11.xpm");
	draw_board(g);
}
