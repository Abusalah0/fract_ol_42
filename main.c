/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:44:54 by abdsalah          #+#    #+#             */
/*   Updated: 2024/11/29 18:49:27 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;
	t_graphics	graphics;

	input_handling(argc, argv, &fractal);
	init_fractal(&fractal);
	init_graphics(&graphics, &fractal);
	render_fractal(&graphics);
	mlx_key_hook(graphics.win, key_handler, &graphics);
	mlx_mouse_hook(graphics.win, mouse_handler, &graphics);
	mlx_hook(graphics.win, 17, 0, close_window, &graphics);
	mlx_loop(graphics.mlx);
	return (0);
}
