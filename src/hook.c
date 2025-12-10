/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:04:41 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/10 14:36:00 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == ESC)
		handle_close(data);
	if (keycode == LEFT)
		data->offset_x -= 0.1 / data->zoom;
	if (keycode == RIGHT)
		data->offset_x += 0.1 / data->zoom;
	if (keycode == UP)
		data->offset_y -= 0.1 / data->zoom;
	if (keycode == DOWN)
		data->offset_y += 0.1 / data->zoom;
	if (keycode == PLUS)
		data->zoom *= 1.1;
	if (keycode == MINUS)
		data->zoom /= 1.1;
	if (keycode == SEVEN && data->max_iter > 10)
		data->max_iter -= 10;
	if (keycode == EIGHT)
		data->max_iter += 10;
	if (keycode == ONE && data->color > 0)
		data->color -= 1;
	if (keycode == TWO && data->color < 3)
		data->color += 1;
	ft_render(data);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_data *data)
{
	double	mr;
	double	mi;

	if (button == WHEELUP || button == WHEELDOWN)
	{
		mr = (x - WIDTH / 2.0)
			/ (0.5 * data->zoom * WIDTH) + data->offset_x;
		mi = (y - HEIGHT / 2.0)
			/ (0.5 * data->zoom * HEIGHT) + data->offset_y;
		if (button == WHEELUP)
			data->zoom *= 1.1;
		else
			data->zoom /= 1.1;
		data->offset_x = mr - ((x - WIDTH / 2.0)
				/ (0.5 * data->zoom * WIDTH));
		data->offset_y = mi - ((y - HEIGHT / 2.0)
				/ (0.5 * data->zoom * HEIGHT));
		ft_render(data);
	}
	return (0);
}
