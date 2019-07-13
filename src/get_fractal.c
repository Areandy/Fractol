/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fractal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:23:57 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/17 13:38:56 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_fractal	*get_fractal(char *str)
{
	static t_fractal	fractals[3] = {
		{"mandelbrot", mandelbrot_set},
		{"julia", julia_set},
		{"tricorn", tricorn}
	};
	int					i;

	i = -1;
	while (++i < 3)
	{
		if (!(ft_strcmp(fractals[i].name, str)))
			return (&fractals[i]);
	}
	return (0);
}
