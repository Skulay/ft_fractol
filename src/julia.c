/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:29:29 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/10 12:39:51 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	julia(t_complex z, t_complex c, int max_iter)
{
	int		i;
	double	r;
	double	im;

	i = 0;
	while (i < max_iter)
	{
		r = z.r * z.r - z.i * z.i + c.r;
		im = 2 * z.r * z.i + c.i;
		z.r = r;
		z.i = im;
		if (z.r * z.r + z.i * z.i > 4)
			break ;
		i++;
	}
	return (i);
}

void	ft_render_julia(t_data *data)
{
	int			x;
	int			y;
	int			iter;
	t_complex	z;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			z.r = (x - WIDTH / 2.0) / (0.5 * data->zoom * WIDTH)
				+ data->offset_x;
			z.i = (y - HEIGHT / 2.0) / (0.5 * data->zoom * HEIGHT)
				+ data->offset_y;
			iter = julia(z, data->julia_c, data->max_iter);
			ft_put_pixel(data, x, y, ft_color(data, iter, data->max_iter));
			x++;
		}
		y++;
	}
}
