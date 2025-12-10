/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:22:21 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/10 12:05:28 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

t_data	*ft_init_struct(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bpp = 0;
	data->line_len = 0;
	data->endian = 0;
	data->zoom = 1.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->max_iter = 50;
	data->type = 0;
	data->color = 0;
	return (data);
}

t_data	*ft_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

t_data	*ft_new_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fractol");
	if (!data->win)
		return (NULL);
	return (data);
}

t_data	*ft_new_image(t_data *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		return (NULL);
	return (data);
}

t_data	*ft_get_addr(t_data *data)
{
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
	return (data);
}
