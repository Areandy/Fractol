/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:21:45 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/17 13:21:49 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

void			julia_set(int x, int y, t_params *p, t_view v)
{
	t_complex	c;
	double		tmp;
	int			i;

	c.re = (((double)x / WIN_WIDTH) * (v.xmax - v.xmin)) * v.zoom
		+ v.xmin + v.offx;
	c.im = (((double)y / WIN_HEIGHT) * (v.ymax - v.ymin)) * v.zoom
		+ v.ymin + v.offy;
	i = -1;
	while ((++i < v.max_iter) && (c.re * c.re + c.im * c.im <= 4))
	{
		tmp = c.re * c.re - c.im * c.im + p->c_re;
		c.im = 2 * c.re * c.im + p->c_im;
		c.re = tmp;
	}
	*(p->image->ptr + (y * WIN_WIDTH + x)) = rgb_magic(i, v.max_iter);
}
