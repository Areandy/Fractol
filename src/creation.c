/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:23:45 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/17 13:23:47 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_image		*create_image(void *mlx_ptr)
{
	t_image	*image;

	if (!(image = (t_image*)malloc(sizeof(t_image))))
		return (0);
	image->image = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	image->ptr = (int*)mlx_get_data_addr(image->image,
		&image->bpp, &image->stride, &image->endian);
	return (image);
}

t_view		create_view(int max_iter)
{
	t_view	view;

	view.xmax = 2;
	view.ymax = 2;
	view.xmin = -2;
	view.ymin = -2;
	view.zoom = 1;
	view.max_iter = max_iter;
	return (view);
}

t_params	*create_params(int max_iter, char *str)
{
	t_params	*params;
	t_mouse		m;

	if (!(params = (t_params*)malloc(sizeof(t_params))))
		return (0);
	m.is_down = 0;
	params->mlx_ptr = mlx_init();
	params->win_ptr = mlx_new_window(params->mlx_ptr, WIN_WIDTH,
		WIN_HEIGHT, "Fractol");
	params->fractal = get_fractal(str);
	params->view = create_view(max_iter);
	params->image = create_image(params->mlx_ptr);
	params->mouse = m;
	params->c_re = 0;
	params->c_im = 0;
	return (params);
}
