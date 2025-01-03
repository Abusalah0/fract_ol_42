/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:04:41 by abdsalah          #+#    #+#             */
/*   Updated: 2025/01/03 09:53:42 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 640
# define HEIGHT 480
# define MAX_ITER 120
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define UP_KEY 65362
# define DOWN_KEY 65364
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define LEFT_CLICK 1
# define ZOOM_FACTOR 1.2
# define MOVE_STEP 0.1

typedef struct s_complex
{
	double		real;
	double		imag;
}				t_complex;

typedef struct s_fractal
{
	char		*name;
	double		shift_x;
	double		shift_y;
	double		zoom;
	double		julia_re;
	double		julia_im;
	int			max_iter;
}				t_fractal;

typedef struct s_graphics
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*data;
	int			bpp;
	int			line_len;
	int			endian;
	t_fractal	*fractal;
}				t_graphics;

void			ft_input_handling(int argc, char **argv, t_fractal *fractal);
int				ft_close_window(t_graphics *graphics);
void			ft_init_fractal(t_fractal *fractal);
void			ft_init_graphics(t_graphics *graphics, t_fractal *fractal);
void			ft_render_fractal(t_graphics *graphics);
int				ft_key_handler(int keycode, t_graphics *graphics);
int				ft_mouse_handler(int button, int x, int y, t_graphics *graphics);
void			ft_error_exit(char *message);
void			ft_free_graphics(t_graphics *graphics);
int				ft_get_pixel_color(t_graphics *graphics, t_complex c);
int				ft_calculate_burning_ship(t_complex c, int max_iterations);
int				ft_calculate_julia(t_complex z, t_fractal *fractal);
int				ft_calculate_mandelbrot(t_complex c, int max_iterations);

#endif