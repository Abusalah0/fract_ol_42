/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:59:28 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/29 19:03:31 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

/*
000000011111111111111111122222233347E7AB322222111100000000000000000000000000000
000001111111111111111122222222333557BF75433222211111000000000000000000000000000
000111111111111111112222222233445C      643332222111110000000000000000000000000
011111111111111111222222233444556C      654433332211111100000000000000000000000
11111111111111112222233346 D978 BCF    DF9 6556F4221111110000000000000000000000
111111111111122223333334469                 D   6322111111000000000000000000000
1111111111222333333334457DB                    85332111111100000000000000000000
11111122234B744444455556A                      96532211111110000000000000000000
122222233347BAA7AB776679                         A32211111110000000000000000000
2222233334567        9A                         A532221111111000000000000000000
222333346679                                    9432221111111000000000000000000
234445568  F                                   B5432221111111000000000000000000
												864332221111111000000000000000000
234445568  F                                   B5432221111111000000000000000000
222333346679                                    9432221111111000000000000000000
2222233334567        9A                         A532221111111000000000000000000
122222233347BAA7AB776679                         A32211111110000000000000000000
11111122234B744444455556A                      96532211111110000000000000000000
1111111111222333333334457DB                    85332111111100000000000000000000
111111111111122223333334469                 D   6322111111000000000000000000000
11111111111111112222233346 D978 BCF    DF9 6556F4221111110000000000000000000000
011111111111111111222222233444556C      654433332211111100000000000000000000000
000111111111111111112222222233445C      643332222111110000000000000000000000000
000001111111111111111122222222333557BF75433222211111000000000000000000000000000
000000011111111111111111122222233347E7AB322222111100000000000000000000000000000
*/

int	ft_calculate_mandelbrot(t_complex c, int max_iterations)
{
	t_complex	z;
	int			iteration;
	double		temp;

	z.real = c.real;
	z.imag = c.imag;
	iteration = 0;
	while (z.real * z.real + z.imag * z.imag <= 4 && iteration < max_iterations)
	{
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		iteration++;
	}
	return (iteration);
}

int	ft_calculate_julia(t_complex z, t_fractal *fractal)
{
	int		iteration;
	double	temp;

	iteration = 0;
	while (z.real * z.real + z.imag * z.imag <= 4
		&& iteration < fractal->max_iter)
	{
		temp = z.real * z.real - z.imag * z.imag + fractal->julia_re;
		z.imag = 2 * z.real * z.imag + fractal->julia_im;
		z.real = temp;
		iteration++;
	}
	return (iteration);
}

int	ft_calculate_burning_ship(t_complex c, int max_iterations)
{
	t_complex	z;
	double		temp;
	int			iteration;

	z.real = c.real;
	z.imag = c.imag;
	iteration = 0;
	while (z.real * z.real + z.imag * z.imag <= 4 && iteration < max_iterations)
	{
		z.real = fabs(z.real);
		z.imag = fabs(z.imag);
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		iteration++;
	}
	return (iteration);
}

void	render_fractal(t_graphics *graphics)
{
	t_complex	c;
	int			color;
	int			y;
	int			x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c.real = (x - WIDTH / 2.0) * 4.0 / WIDTH / graphics->fractal->zoom
				+ graphics->fractal->shift_x;
			c.imag = (y - HEIGHT / 2.0) * 4.0 / WIDTH / graphics->fractal->zoom
				+ graphics->fractal->shift_y;
			color = ft_get_pixel_color(graphics, c);
			graphics->data[y * WIDTH + x] = color;
		}
	}
	mlx_put_image_to_window(graphics->mlx, graphics->win, graphics->img, 0, 0);
}
