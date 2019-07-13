/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavreni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:54:55 by mlavreni          #+#    #+#             */
/*   Updated: 2019/01/17 13:55:03 by mlavreni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define THREADS_AMOUNT 10

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "mlx.h"

typedef struct				s_complex
{
	double			re;
	double			im;
}							t_complex;

typedef struct				s_image
{
	void			*image;
	int				*ptr;
	int				bpp;
	int				stride;
	int				endian;
}							t_image;

typedef struct				s_view
{
	double			xmax;
	double			xmin;
	double			ymax;
	double			ymin;
	double			zoom;
	double			offx;
	double			offy;
	int				max_iter;
}							t_view;

typedef struct s_params		t_params;
typedef void				(*t_func)(int x, int y, t_params *params, t_view v);
typedef struct				s_fractal
{
	char			*name;
	t_func			func;
}							t_fractal;

typedef struct				s_mouse
{
	int				x;
	int				y;
	int				is_down;
}							t_mouse;

typedef struct				s_thread
{
	int				id;
	pthread_t		thread_id;
	t_params		*params;
}							t_thread;

struct						s_params
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_thread		threads[THREADS_AMOUNT];
	t_image			*image;
	t_fractal		*fractal;
	t_view			view;
	t_mouse			mouse;
	double			c_re;
	double			c_im;
};

void						julia_set(int x, int y, t_params *p, t_view v);
void						mandelbrot_set(int x, int y, t_params *p, t_view v);
void						tricorn(int x, int y, t_params *p, t_view v);
int							rgb_magic(int n, int max_iter);
t_image						*create_image(void *mlx_ptr);
t_fractal					*get_fractal(char *str);
t_view						create_view(int max_iter);
t_params					*create_params(int max_iter, char *str);
int							change_julia_const(int x, int y, t_params *p);
void						zoom(int x, int y, double diff, t_params *p);
int							key_press(int key, void *param);
int							mouse_move(int x, int y, t_params *p);
int							mouse_down(int button, int xm, int y, t_params *p);
int							mouse_up(int button, int x, int y, t_params *p);
int							is_in_window(int x, int y);
int							display_list(void);
void						*render(void *t);
int							create_threads(t_params *p);

#endif
