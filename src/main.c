/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:42:30 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/17 13:42:32 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			is_in_window(int x, int y)
{
	if ((x >= 0 && x <= WIN_WIDTH) && (y >= 0 && y <= WIN_HEIGHT))
		return (1);
	return (0);
}

int			key_press(int key, void *param)
{
	if (key == 53 && param)
		exit(0);
	return (1);
}

int			display_list(void)
{
	ft_putstr("Avalible fractals:");
	return (ft_putstr("\n\t[mandelbrot]\n\t[julia]\n\t[tricorn]\n"));
}

int			main(int ac, char **av)
{
	t_params	*params;
	int			max_iter;

	if (ac < 2)
		return (display_list());
	max_iter = (ac == 3 && (ft_atoi(av[2]) > 0)) ? ft_atoi(av[2]) : 50;
	if (get_fractal(av[1]))
		params = create_params(max_iter, av[1]);
	else
		return (display_list());
	create_threads(params);
	mlx_hook(params->win_ptr, 2, 1L, key_press, params);
	mlx_hook(params->win_ptr, 6, 1L << 6, mouse_move, params);
	mlx_hook(params->win_ptr, 4, 1L << 2, mouse_down, params);
	mlx_hook(params->win_ptr, 5, 1L << 3, mouse_up, params);
	mlx_loop(params->mlx_ptr);
	return (0);
}
