/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:21:27 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/03 08:22:24 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int ft_color(t_data *data, int iter, int max_iter)
{
	double t;

	if (iter == max_iter)
		return 0x000000;
	t = (double)iter / (double)max_iter;
	if (data->color == 0)
		return ft_color_scheme0(t);
	if (data->color == 1)
		return ft_color_scheme1(t);
	if (data->color == 2)
		return ft_color_scheme2(t);
	if (data->color == 3)
		return ft_color_scheme3(t);
	return ft_color_scheme0(t);
}

int ft_color_scheme0(double t) // dégradé bleu → jaune → blanc
{
	int r = (int)(9 * (1 - t) * t * t * t * 255);
	int g = (int)(15 * (1 - t) * (1 - t) * t * 255);
	int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

int ft_color_scheme1(double t) // palette 1 : dégradé rouge → noir → blanc
{
	int r = (int)(t * 255);
	int g = (int)((1 - t) * t * 255);
	int b = (int)((1 - t) * 255);
	return ((r << 16) | (g << 8) | b);
}

int ft_color_scheme2(double t) // palette 2 : violet → bleu → turquoise
{
	int r = (int)((1 - t) * 128);
	int g = (int)(t * 255);
	int b = (int)(128 + t * 127);
	return ((r << 16) | (g << 8) | b);
}

// int ft_color_scheme3(double t) // palette 3 : feu (orange → rouge → jaune)
// {
// 	int r = 255;
// 	int g = (int)(t * 150);
// 	int b = (int)((1 - t) * 80);
// 	return ((r << 16) | (g << 8) | b);
// }

int	ft_color_scheme3(double t)
{
	double	k1;
	double	k2;
	double	k3;
	double	w;
	double	g;
	double	r;
	double	gc;
	double	b;

	// fréquences imbriquées
	k1 = t * 6.28318 * 5.0;   // 5 cycles
	k2 = t * 6.28318 * 11.0;  // haute fréquence
	k3 = t * 6.28318 * 23.0;  // ultra haute fréquence

	// feedback psychédélique interne
	w = 0.5 + 0.5 * sin(t * 40.0 + sin(t * 12.0) * 3.0);

	// gamma dynamique explosif
	g = 0.2 + 1.8 * w;

	// mélange spectral
	r = pow(0.5 + 0.5 * sin(k1 + 0.0)
	      + 0.3 * sin(k2 + 1.1)
	      + 0.15 * sin(k3 + 2.3), g);

	gc = pow(0.5 + 0.5 * sin(k1 + 2.094)
	       + 0.3 * sin(k2 + 3.0)
	       + 0.15 * sin(k3 + 4.1), g);

	b = pow(0.5 + 0.5 * sin(k1 + 4.188)
	      + 0.3 * sin(k2 + 5.7)
	      + 0.15 * sin(k3 + 0.8), g);

	// // clamp (optionnel mais sécurisant)
	// if (r < 0) r = 0; if (r > 1) r = 1;
	// if (gc < 0) gc = 0; if (gc > 1) gc = 1;
	// if (b < 0) b = 0; if (b > 1) b = 1;

	return (((int)(r * 255) << 16)
		| ((int)(gc * 255) << 8)
		| (int)(b * 255));
}

// int	ft_color_scheme3(double t)
// {
// 	double	k;
// 	double	m;
// 	double	g;
// 	int		r;
// 	int		gc;
// 	int		b;

// 	// accélération : boucle des couleurs 3 fois
// 	k = t * 18.8495; // 6π

// 	// modulation psycho : wobble sin
// 	m = 0.5 + 0.5 * sin(t * 12.566); // 4π

// 	// gamma dynamique pour saturation néon
// 	g = 0.2 + 0.8 * m;

// 	r = (int)(255 * pow(0.5 + 0.5 * sin(k + 0.0), g));
// 	gc = (int)(255 * pow(0.5 + 0.5 * sin(k + 2.094), g));
// 	b = (int)(255 * pow(0.5 + 0.5 * sin(k + 4.188), g));
// 	return ((r << 16) | (gc << 8) | b);
// }

// int	ft_color_scheme3(double t)
// {
// 	double	k;
// 	double	gm;
// 	int		r;
// 	int		g;
// 	int		b;

// 	k = t * 6.28318;        // 2π
// 	gm = pow(t, 0.3);       // gamma boost : couleurs plus explosives
// 	r = (int)(255 * pow(0.5 + 0.5 * sin(k + 0.0), gm));
// 	g = (int)(255 * pow(0.5 + 0.5 * sin(k + 2.094), gm));
// 	b = (int)(255 * pow(0.5 + 0.5 * sin(k + 4.188), gm));
// 	return ((r << 16) | (g << 8) | b);
// }

// int	ft_color_scheme3(double t)
// {
// 	double	k;
// 	int		r;
// 	int		g;
// 	int		b;

// 	k = t * 6.28318; // 2π
// 	r = (int)(255 * (0.5 + 0.5 * sin(k + 0.0)));
// 	g = (int)(255 * (0.5 + 0.5 * sin(k + 2.094))); // +120°
// 	b = (int)(255 * (0.5 + 0.5 * sin(k + 4.188))); // +240°
// 	return ((r << 16) | (g << 8) | b);
// }

// int ft_color_scheme3(double t)
// {
// 	double r, g, b;
// 	double h = 360.0 * t;	// Hue
// 	double s = 1.0;			// Saturation
// 	double v = 1.0;			// Value

// 	double c = v * s;
// 	double x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
// 	double m = v - c;
// 	double rr, gg, bb;
// 	if (h < 60)
// 		rr = c, gg = x, bb = 0;
// 	else if (h < 120)
// 		rr = x, gg = c, bb = 0;
// 	else if (h < 180)
// 		rr = 0, gg = c, bb = x;
// 	else if (h < 240)
// 		rr = 0, gg = x, bb = c;
// 	else if (h < 300)
// 		rr = x, gg = 0, bb = c;
// 	else
// 		rr = c, gg = 0, bb = x;
// 	r = (rr + m) * 255;
// 	g = (gg + m) * 255;
// 	b = (bb + m) * 255;

// 	return (((int)r << 16) | ((int)g << 8) | (int)b);
// }
