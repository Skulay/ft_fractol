/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:23:21 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/08 15:47:51 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H
# define FT_FRACTOL_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MANDELBROT 0
# define JULIA 1
# define BURNSHIP 2
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364
# define PLUS 61
# define MINUS 45
# define SEVEN 55
# define EIGHT 56
# define ONE 49
# define TWO 50
# define WHEELUP 4
# define WHEELDOWN 5
# define BLACK 0x000000

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	double		zoom;
	double		offset_x;
	double		offset_y;
	int			max_iter;
	int			type;
	int			color;
	t_complex	julia_c;
}	t_data;

// fonction pour la struct
t_data	*ft_init(void);
t_data	*ft_new_window(t_data *data);
t_data	*ft_new_image(t_data *data);
t_data	*ft_get_addr(t_data *data);

// parsing
void	parse_args(t_data *data, int ac, char **av);

// rendu
void	ft_render(t_data *data);

// mandelbrot
int		mandelbrot(t_complex z, t_complex c, int max_iter);
void	ft_render_mandelbrot(t_data *d, t_complex z, t_complex c);

// julia
int		julia(t_complex z, t_complex c, int max_iter);
void	ft_render_julia(t_data *d, t_complex z);

// burningship
int		burning_ship(t_complex z, t_complex c, int max_iter);
void	ft_render_burning_ship(t_data *data, t_complex z, t_complex c);

// utilitaire
double	ft_atod(const char *s);
void	ft_put_pixel(t_data *data, int x, int y, int color);
int		close_window(t_data *data);
void	ft_how_to_use(void);

// recup d'input keyboard
int		key_handler(int keycode, t_data *data);
int		mouse_handler(int button, int x, int y, t_data *data);

// color
int		ft_color(t_data *data, int iter, int max_iter);
int		ft_color_scheme0(double t);
int		ft_color_scheme1(double t);
int		ft_color_scheme2(double t);
int		ft_color_scheme3(double t);

#endif
