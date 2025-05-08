/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:43:43 by abdsalah          #+#    #+#             */
/*   Updated: 2025/01/03 10:08:12 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	ft_close_window(t_graphics *graphics)
{
	ft_free_graphics(graphics);
	exit(0);
}

void	ft_error_exit(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	ft_free_graphics(t_graphics *graphics)
{
	if (graphics->img)
	{
		mlx_destroy_image(graphics->mlx, graphics->img);
		graphics->img = NULL;
	}
	if (graphics->win)
	{
		mlx_destroy_window(graphics->mlx, graphics->win);
		graphics->win = NULL;
	}
	if (graphics->mlx)
	{
		mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
		graphics->mlx = NULL;
	}
}
