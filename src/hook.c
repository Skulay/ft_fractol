/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:04:41 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/03 14:32:26 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
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
	if (keycode == SEVEN)
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
