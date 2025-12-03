/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:04:41 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/03 07:51:03 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC
		close_window(data);
	if (keycode == 65361) // LEFT
		data->offset_x -= 0.1 / data->zoom;
	if (keycode == 65363) // RIGHT
		data->offset_x += 0.1 / data->zoom;
	if (keycode == 65362) // UP
		data->offset_y -= 0.1 / data->zoom;
	if (keycode == 65364) // DOWN
		data->offset_y += 0.1 / data->zoom;
	if (keycode == 61) // +
		data->zoom *= 1.1;
	if (keycode == 45) // -
		data->zoom /= 1.1;
	if (keycode == 55) // 7
		data->max_iter -= 10;
	if (keycode == 56) // 8
		data->max_iter += 10;
	if (keycode == 49 && data->color > 0) // 1
		data->color -= 1;
	if (keycode == 50 && data->color < 3) // 2
		data->color += 1;
	ft_render(data);
	return (0);
}
