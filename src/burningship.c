/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:39:02 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/10 12:39:08 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	burning_ship(t_complex z, t_complex c, int max_iter)
{
	int		i;
	double	abs_r;
	double	abs_i;

	i = 0;
	while (i < max_iter)
	{
		abs_r = fabs(z.r);
		abs_i = fabs(z.i);
		z.r = abs_r * abs_r - abs_i * abs_i + c.r;
		z.i = 2 * abs_r * abs_i + c.i;
		if (z.r * z.r + z.i * z.i > 4)
			break ;
		i++;
	}
	return (i);
}

void	ft_render_burning_ship(t_data *data)
{
	int			x;
	int			y;
	int			iter;
	t_complex	z;
	t_complex	c;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c.r = (x - WIDTH / 2.0) / (0.5 * data->zoom * WIDTH)
				+ data->offset_x;
			c.i = (y - HEIGHT / 2.0) / (0.5 * data->zoom * HEIGHT)
				+ data->offset_y;
			z.r = 0;
			z.i = 0;
			iter = burning_ship(z, c, data->max_iter);
			ft_put_pixel(data, x++, y, ft_color(data, iter, data->max_iter));
		}
		y++;
	}
}
