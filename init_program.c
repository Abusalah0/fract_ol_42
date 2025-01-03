/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:42:40 by abdsalah          #+#    #+#             */
/*   Updated: 2025/01/03 10:19:27 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
/*
** ft_init_fractal
** ---------------
** Initializes the fractal structure with default values.
*/
void	ft_init_fractal(t_fractal *fractal)
{
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->max_iter = MAX_ITER;
	fractal->julia_re = -0.512511498387847167;
	fractal->julia_im = 0.521295573094847167;
}
/*
** ft_init_graphics_struct
** -----------------------
** Initializes the graphics structure with NULL values.
*/
static void	ft_init_graphics_struct(t_graphics *graphics)
{
	graphics->mlx = NULL;
	graphics->win = NULL;
	graphics->img = NULL;
	graphics->data = NULL;
	graphics->bpp = 0;
	graphics->line_len = 0;
	graphics->endian = 0;
	graphics->fractal = NULL;
}
/*
** ft_free_graphics
** ----------------
** intiliaze the graphics structure with the MLX connection, window, image
** and the data address for the image
** also set graphics->fractal pointer to the fractal structure.
*/
void	ft_init_graphics(t_graphics *graphics, t_fractal *fractal)
{
	ft_init_graphics_struct(graphics);
	graphics->mlx = mlx_init();
	if (!graphics->mlx)
		ft_error_exit("Failed to initialize MLX");
	graphics->win = mlx_new_window(graphics->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!graphics->win)
	{
		ft_free_graphics(graphics);
		ft_error_exit("Failed to create MLX window");
	}
	graphics->img = mlx_new_image(graphics->mlx, WIDTH, HEIGHT);
	if (!graphics->img)
	{
		ft_free_graphics(graphics);
		ft_error_exit("Failed to create MLX image");
	}
	graphics->data = (int *)mlx_get_data_addr(graphics->img, &graphics->bpp,
			&graphics->line_len, &graphics->endian);
	if (!graphics->data)
	{
		ft_free_graphics(graphics);
		ft_error_exit("Failed to get image data address");
	}
	graphics->fractal = fractal;
}
/*
** ft_input_handling
** -----------------
** Validates the command-line arguments and sets the fractal name.
*/
void	ft_input_handling(int argc, char **argv, t_fractal *fractal)
{
	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fractol <fractal_name>", 2);
		ft_putendl_fd("Available fractals: mandelbrot, julia, burning_ship", 2);
		exit(EXIT_FAILURE);
	}
	fractal->name = argv[1];
	if (ft_strcmp(fractal->name, "mandelbrot") && ft_strcmp(fractal->name,
			"julia") && ft_strcmp(fractal->name, "burning_ship"))
	{
		ft_putendl_fd("Available fractals: mandelbrot, julia, burning_ship", 2);
		exit(EXIT_FAILURE);
	}
}
