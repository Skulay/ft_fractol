/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:29:38 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/03 12:59:45 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
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
	(void)!write(2, "Usage:\n", 7);
	(void)!write(2, "  ./fractol mandelbrot\n", 23);
	(void)!write(2, "  ./fractol julia <real> <imag>\n", 32);
	(void)!write(2, "  ./fractol burningship\n", 24);
	(void)!write(2, "Exemples:\n", 10);
	(void)!write(2, "  ./fractol julia -0.8 0.156\n", 28);
	exit(1);
}
