/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:22:18 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/17 13:22:20 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

void			tricorn(int x, int y, t_params *p, t_view v)
{
	t_complex	c;
	t_complex	t;
	double		tmp;
	int			i;

	c.re = (((double)x / WIN_WIDTH) * (v.xmax - v.xmin)) * v.zoom
		+ v.xmin + v.offx;
	c.im = (((double)y / WIN_HEIGHT) * (v.ymax - v.ymin)) * v.zoom
		+ v.ymin + v.offy;
	t.re = c.re;
	t.im = c.im;
	i = -1;
	while ((++i < v.max_iter) && (t.re * t.re + t.im * t.im <= 4))
	{
		tmp = t.re * t.re - t.im * t.im + c.re;
		t.im = -2 * t.re * t.im + c.im;
		t.re = tmp;
	}
	*(p->image->ptr + (y * WIN_WIDTH + x)) = rgb_magic(i, v.max_iter);
}
