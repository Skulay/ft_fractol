/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:46:07 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/03 12:09:35 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_render(t_data *data)
{
	t_complex	x;
	t_complex	y;

	if (data->type == 0)
		ft_render_mandelbrot(data, x, y);
	else if (data->type == 1)
		ft_render_julia(data, x);
	else
		ft_render_burning_ship(data, x, y);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
