/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:08:46 by albaud            #+#    #+#             */
/*   Updated: 2023/03/02 20:35:35 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <pthread.h>
#define TIME 1
int m = 0;

void	error(char *n)
{
	printf("snake: %s\n", n);
	exit(1);
}

int	inf_hook(t_game *g)
{
	static int	count = 0;
	static t_v	v = (t_v){0, -1};
	int			i;
	static int	dead = 0;

	if (v.size == -1)
		v = v_new(INPUT, 0);
	count += 1;
	if (m == 2 && count > TIME)
	{
		g->play = 0;
		count = max_max(g, 5);
		g->play = 1;
		i = step(g, count);
		if (i == 0)
			++dead;
		// if (dead >= 10)
		// {
		// 	dead = 0;
		// 	reset_game(g);
		// }
		if (m_max(&g->board) == 11)
		{
			m = 0;
		}
		count = 0;
	}
	return (0);
}

int	key_mmove(int k, t_game *s)
{
	(void) s;
	if (k == KEYCODE_D)
		step(s, 0);
	if (k == KEYCODE_SPACE)
		reset_game(s);
	if (k == KEYCODE_S)
		step(s, 1);
	if (k == KEYCODE_A)
		step(s, 2);
	if (k == KEYCODE_W)
		step(s, 3);
	if (k == KEYCODE_R)
		m = 1;
	if (k == KEYCODE_T)
		m = 2;
	if (k == KEYCODE_Z)
		m = 0;
	draw_board(s);
	return (0);
}

t_info	*get_info(t_info *inf)
{
	inf->inputs = INPUT;
	inf->hiden_layers = 1;
	inf->outputs = 4;
	inf->data_size = 0;
	return (inf);
}

int	main(int argc, char **argv)
{
	t_game	g;

	(void) argc;
	(void) argv;
	g.play = 1;
	init_game(&g, 4, 4);
	mlx_loop_hook(g.w.mlx, inf_hook, &g);
	mlx_loop(g.w.mlx);
	return (0);
}

/*

		if (m == 1 && count > TIME)
	{
		get_state(g, &v);
		ia_forward(&g->net, &v);
		i = step(g, v_maxi(&g->net.predicted_output));
		if (i == 0)
			step(g, (int)rand_range(0, 4));
		visualize(&g->vis, &v);
	}
	
	get_info(&g.net.info);
	g.net.info.hiden_layers_size = (int []){24, 16, 20};
	ia_init_net(
		&g.net,
		argv[2],
		&g.net.info);
	init_visualizer(&g.vis, &g.net);
	g.vis.out_label = (char *[]){"right", "down", "left", "up", 0};
	if (argc == 4)
		ia_load(&g.net, argv[3]);
	// if (atoi(argv[1]))
	// 	train(&g, atoi(argv[1]), argc == 4);
	g.play = 1;
*/