/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:59:25 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/30 14:43:15 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static void	zoom(t_graphics *graphics, double zoom_factor)
{
	double	width;
	double	height;
	double	new_width;
	double	new_height;

	width = WIDTH / graphics->fractal->zoom;
	height = HEIGHT / graphics->fractal->zoom;
	new_width = width / zoom_factor;
	new_height = height / zoom_factor;
	graphics->fractal->zoom *= zoom_factor;
	graphics->fractal->shift_x += (width - new_width) / 2.0 / WIDTH;
	graphics->fractal->shift_y += (height - new_height) / 2.0 / HEIGHT;
}

int	key_handler(int keycode, t_graphics *graphics)
{
	double	move_step;

	move_step = MOVE_STEP / graphics->fractal->zoom;
	if (keycode == ESC_KEY)
	{
		mlx_destroy_image(graphics->mlx, graphics->img);
		mlx_clear_window(graphics->mlx, graphics->win);
		mlx_destroy_window(graphics->mlx, graphics->win);
		mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
		exit(0);
	}
	else if (keycode == LEFT_KEY)
		graphics->fractal->shift_x -= move_step;
	else if (keycode == RIGHT_KEY)
		graphics->fractal->shift_x += move_step;
	else if (keycode == UP_KEY)
		graphics->fractal->shift_y -= move_step;
	else if (keycode == DOWN_KEY)
		graphics->fractal->shift_y += move_step;
	render_fractal(graphics);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_graphics *graphics)
{
	double	zoom_center_x;
	double	zoom_center_y;

	zoom_center_x = (x - WIDTH / 2.0) * 4.0 / WIDTH / graphics->fractal->zoom
		+ graphics->fractal->shift_x;
	zoom_center_y = (y - HEIGHT / 2.0) * 4.0 / WIDTH / graphics->fractal->zoom
		+ graphics->fractal->shift_y;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		graphics->fractal->shift_x = zoom_center_x;
		graphics->fractal->shift_y = zoom_center_y;
		if (button == MOUSE_SCROLL_UP)
			zoom(graphics, ZOOM_FACTOR);
		else if (button == MOUSE_SCROLL_DOWN)
			zoom(graphics, 1.0 / ZOOM_FACTOR);
		render_fractal(graphics);
	}
	if (button == LEFT_CLICK && !ft_strcmp(graphics->fractal->name, "julia"))
	{
		graphics->fractal->julia_re = zoom_center_x;
		graphics->fractal->julia_im = zoom_center_y;
		render_fractal(graphics);
	}
	return (0);
}
