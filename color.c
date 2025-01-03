/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:59:48 by abdsalah          #+#    #+#             */
/*   Updated: 2025/01/03 09:52:55 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
Color Gradients: The code uses smooth polynomial functions to generate red,
green, and blue color values based on the iteration count (color).
The result is a smooth gradient of colors that varies as the point takes
longer to escape the fractal, creating a colorful "map" of escape times.
t: The ratio of the current iteration to the maximum iteration,
	which influences the color.
Polynomial curves: (1 - t) * t * t * t, (1 - t) * (1 - t) * t * t,
and (1 - t) * (1 - t) * (1 - t) * t are designed to give different color
transitions for red, green, and blue components.
The constants (9, 15, 8.5) adjust the intensity of the color components.
*/
static int	ft_get_color(int color, t_fractal *fractal)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	t = (double)color / fractal->max_iter;
	red = (int)(9 * (1 - t) * t * t * t * 255);
	green = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	color = (red << 16) | (green << 8) | blue;
	return (color);
}

int	ft_get_pixel_color(t_graphics *graphics, t_complex c)
{
	int	color;

	color = 0;
	if (graphics->fractal->name && ft_strcmp(graphics->fractal->name,
			"mandelbrot") == 0)
		color = ft_calculate_mandelbrot(c, graphics->fractal->max_iter);
	else if (graphics->fractal->name && ft_strcmp(graphics->fractal->name,
			"julia") == 0)
		color = ft_calculate_julia(c, graphics->fractal);
	else if (graphics->fractal->name && ft_strcmp(graphics->fractal->name,
			"burning_ship") == 0)
		color = ft_calculate_burning_ship(c, graphics->fractal->max_iter);
	if (color == graphics->fractal->max_iter)
		color = 0x000000;
	else
	{
		color = ft_get_color(color, graphics->fractal);
	}
	return (color);
}
