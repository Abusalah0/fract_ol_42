/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:59:28 by abdsalah          #+#    #+#             */
/*   Updated: 2025/01/03 09:54:03 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"


/*
** Function: ft_calculate_mandelbrot
** ---------------------------------
** Computes the number of iterations for a point in the Mandelbrot set.
**
** Mandelbrot equation:
**   z(n+1) = z(n)^2 + c
**   - z(n): Current complex number in the iteration.
**   - c: Initial complex number (constant).
**
** Parameters:
** - c: Complex number representing the initial point on the complex plane.
** - max_iterations: Maximum number of iterations to compute.
**
** Returns:
** - The number of iterations before the point diverges or reaches the maximum.
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

/*
** Function: ft_calculate_julia
** ----------------------------
** Computes the number of iterations for a point in the Julia set.
**
** Julia equation:
**   z(n+1) = z(n)^2 + c
**   - z(n): Current complex number in the iteration.
**   - c: Constant complex number specific to the Julia set.
**
** Parameters:
** - z: Initial complex number (z0) to compute the iteration for.
** - fractal: Pointer to the fractal structure containing Julia parameters.
**
** Returns:
** - The number of iterations before the point diverges or reaches the maximum.
*/
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

/*
** Function: ft_calculate_burning_ship
** -----------------------------------
** Computes the number of iterations for a point in the Burning Ship fractal.
**
** Burning Ship equation:
**   z(n+1) = (|Re(z(n))| + i|Im(z(n))|)^2 + c
**   - Re(z(n)): Real part of the current complex number.
**   - Im(z(n)): Imaginary part of the current complex number.
**   - c: Initial complex number (constant).
**
** Parameters:
** - c: Complex number representing the initial point on the complex plane.
** - max_iterations: Maximum number of iterations to compute.
**
** Returns:
** - The number of iterations before the point diverges or reaches the maximum.
*/
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

/*
** Function: render_fractal
** ------------------------
** Renders the fractal image by iterating over each pixel and mapping it to
** the corresponding point on the complex plane.
**
** Parameters:
** - graphics: Pointer to the graphics structure containing fractal data and
**   rendering information.
**
** Notes:
** - This function calculates the color for each pixel based on the fractal
**   type and updates the image data.
*/
void	ft_render_fractal(t_graphics *graphics)
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
			// Map pixel coordinates to complex plane.
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
