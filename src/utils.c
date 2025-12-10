/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:29:38 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/10 12:44:31 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_data *data)
{
	if (!data)
		return (0);
    mlx_hook(data->win, 2, 0, NULL, NULL);
    mlx_hook(data->win, 4, 0, NULL, NULL);
    mlx_hook(data->win, 17, 0, NULL, NULL);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	data->img = NULL;
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	data->mlx = NULL;
	free(data);
	exit(0);
	return (0);
}


static void	skip_spaces(const char **s)
{
	while (**s == ' ' || (**s >= 9 && **s <= 13))
		(*s)++;
}

double	ft_atod(const char *s)
{
	double	result;
	double	sign;
	double	frac;

	result = 0.0;
	sign = 1.0;
	frac = 1.0;
	skip_spaces(&s);
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1.0;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		result = result * 10.0 + (*s++ - '0');
	if (*s++ == '.')
	{
		while (*s >= '0' && *s <= '9')
		{
			frac *= 0.1;
			result += (*s++ - '0') * frac;
		}
	}
	return (result * sign);
}

void	ft_how_to_use(void)
{
	ft_printf("Usage:\n  ./fractol mandelbrot\n");
	ft_printf("  ./fractol julia <real> <imag>\n  ./fractol burningship\n");
	ft_printf("Exemples:\n  ./fractol julia -0.8 0.156\n");
	exit(1);
}
