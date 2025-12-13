/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:21:27 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/13 21:28:47 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	ft_color(t_data *data, int iter, int max_iter)
{
	double	t;

	if (iter == max_iter)
		return (BLACK);
	t = (double)iter / (double)max_iter;
	if (t < 0.05)
		return (BLACK);
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
	double	k;
	int		r;
	int		g;
	int		b;

	if (t > 0.5)
	{
		k = (t - 0.5) / 0.5;
		r = (int)(0 * (1 - k) + 0 * k);
		g = (int)(0 * (1 - k) + 80 * k);
		b = (int)(0 * (1 - k) + 255 * k);
	}
	else
	{
		k = t / 0.5;
		r = (int)(0 * (1 - k) + 255 * k);
		g = (int)(80 * (1 - k) + 200 * k);
		b = (int)(255 * (1 - k) + 50 * k);
	}
	return ((r << 16) | (g << 8) | b);
}
