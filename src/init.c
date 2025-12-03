/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:22:21 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/03 12:01:45 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

t_data	*ft_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data);
		return (NULL);
	}
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bpp = 0;
	data->line_len = 0;
	data->endian = 0;
	data->zoom = 1.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->max_iter = 100;
	data->type = 0;
	data->color = 0;
	return (data);
}

t_data	*ft_new_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fractol");
	if (!data->win)
	{
		close_window(data);
		return (NULL);
	}
	return (data);
}

t_data	*ft_new_image(t_data *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	return (data);
}

t_data	*ft_get_addr(t_data *data)
{
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
	return (data);
}
