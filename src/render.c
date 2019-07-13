/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:23:20 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/17 13:23:22 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			*render(void *thr)
{
	t_thread	*t;
	int			x;
	int			y;
	t_complex	tmp;

	t = (t_thread*)thr;
	tmp.re = WIN_HEIGHT / THREADS_AMOUNT * t->id;
	tmp.im = WIN_HEIGHT / THREADS_AMOUNT * (t->id + 1);
	y = tmp.re - 1;
	while (++y < tmp.im)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			t->params->fractal->func(x, y, t->params, t->params->view);
	}
	return (NULL);
}

int				create_threads(t_params *p)
{
	int			i;

	i = -1;
	while (++i < THREADS_AMOUNT)
	{
		p->threads[i].id = i;
		p->threads[i].params = p;
		pthread_create(&(p->threads[i].thread_id),
			NULL, render, &(p->threads[i]));
	}
	i = -1;
	while (++i < THREADS_AMOUNT)
		pthread_join(p->threads[i].thread_id, NULL);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->image->image, 0, 0);
	return (1);
}
