/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:04:24 by albaud            #+#    #+#             */
/*   Updated: 2023/03/01 16:18:15 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_board(t_game *game)
{
	int		x;
	int		y;

	ft_clean_canvas(game->w.cvs);
	mlx_clear_window(game->w.mlx, game->w.win);
	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
		{
			if (game->board.arr[x].arr[y])
				ft_putimg(game->w,
					game->piece[(int)game->board.arr[x].arr[y] - 1].img,
					(t_vector){x * PSIZE, y * PSIZE, 0, 0});
		}
	}

}
