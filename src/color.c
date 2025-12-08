/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:21:27 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/08 15:25:38 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	ft_color(t_data *data, int iter, int max_iter)
{
	double	t;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / (double)max_iter;
	if (data->color == 0)
		return (ft_color_scheme0(t));
	if (data->color == 1)
		return (ft_color_scheme1(t));
	if (data->color == 2)
		return (ft_color_scheme2(t));
	if (data->color == 3)
		return (ft_color_scheme3(t));
	return (ft_color_scheme0(t));
}

int	ft_color_scheme0(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

int	ft_color_scheme1(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(t * 255);
	g = (int)((1 - t) * t * 255);
	b = (int)((1 - t) * 255);
	return ((r << 16) | (g << 8) | b);
}

int	ft_color_scheme2(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)((1 - t) * 128);
	g = (int)(t * 255);
	b = (int)(128 + t * 127);
	return ((r << 16) | (g << 8) | b);
}

int	ft_color_scheme3(double t)
{
	int	r;
	int	g;
	int	b;

	r = 255;
	g = (int)(t * 150);
	b = (int)((1 - t) * 80);
	return ((r << 16) | (g << 8) | b);
}
