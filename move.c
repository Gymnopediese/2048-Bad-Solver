/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:11:20 by albaud            #+#    #+#             */
/*   Updated: 2023/03/01 12:57:11 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_move(t_run	*run)
{
	t_move	*m;
	t_move	*t;

	m = run->head;
	while (m)
	{
		t = m->next;
		free(m->input->arr);
		free(m->output->arr);
		free(m->input);
		free(m->output);
		free(m);
		m = t;
	}
	run->head = 0;
	run->tail = 0;
	run->size = 0;
}

void	free_runs(t_run *runs)
{
	int		i;

	i = 0;
	while (++i < POPSIZE)
		free_move(&runs[i]);
}

void	add_move(t_run *r, int m, t_v *state, double v)
{
	t_move	*nb;

	nb = alo(1, sizeof(t_move));
	nb->input = alo(1, sizeof(t_v));
	nb->output = alo(1, sizeof(t_v));
	*nb->input = v_new(INPUT, 0);
	*nb->output = v_new(4, 0);
	v_copy(nb->input, state);
	nb->output->arr[m] = 1;
	nb->value = v;
	nb->next = 0;
	if (r->head == 0)
	{
		r->head = nb;
		r->tail = nb;
		r->score = 0;
	}
	else
	{
		r->tail->next = nb;
		r->tail = nb;
	}
	r->size += 1;
}
