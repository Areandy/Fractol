/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:23:34 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/17 13:23:35 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			change_julia_const(int x, int y, t_params *p)
{
	p->c_re = ((double)x / WIN_WIDTH) *
		(p->view.xmax - p->view.xmin) + p->view.xmin;
	p->c_im = ((double)y / WIN_HEIGHT) *
		(p->view.ymax - p->view.ymin) + p->view.ymin;
	create_threads(p);
	return (0);
}

int			mouse_move(int x, int y, t_params *p)
{
	double	width;
	double	height;
	int		lastx;
	int		lasty;

	if (!(is_in_window(x, y)))
		return ((p->mouse.is_down = 0));
	lastx = p->mouse.x;
	lasty = p->mouse.y;
	p->mouse.x = x;
	p->mouse.y = y;
	if (p->fractal->func == julia_set)
		return (change_julia_const(x, y, p));
	if (p->mouse.is_down)
	{
		width = (p->view.xmax - p->view.xmin) * p->view.zoom;
		height = (p->view.ymax - p->view.ymin) * p->view.zoom;
		p->view.offx += (double)(lastx - p->mouse.x)
			/ WIN_WIDTH * width;
		p->view.offy += (double)(lasty - p->mouse.y)
			/ WIN_HEIGHT * height;
		create_threads(p);
	}
	return (1);
}

void		zoom(int x, int y, double diff, t_params *p)
{
	double	width;
	double	height;

	width = (p->view.xmax - p->view.xmin) * (p->view.zoom * diff)
		- (p->view.xmax - p->view.xmin) * (p->view.zoom);
	height = (p->view.ymax - p->view.ymin) * (p->view.zoom * diff)
		- (p->view.ymax - p->view.ymin) * (p->view.zoom);
	p->view.zoom *= diff;
	p->view.offx -= ((double)x / WIN_WIDTH) * width;
	p->view.offy -= ((double)y / WIN_HEIGHT) * height;
}

int			mouse_down(int button, int x, int y, t_params *p)
{
	if (button == 4)
	{
		zoom(x, y, 1 / 1.1, p);
		create_threads(p);
	}
	else if (button == 5)
	{
		zoom(x, y, 1.1, p);
		create_threads(p);
	}
	if (y < 0)
		return (0);
	if (button == 1)
		p->mouse.is_down = 1;
	return (0);
}

int			mouse_up(int button, int x, int y, t_params *p)
{
	if ((button == 1) && is_in_window(x, y))
		p->mouse.is_down = (p->mouse.is_down == 1) ? 0 : 1;
	return (0);
}
