/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:29:34 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/16 07:16:01 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	parse_args(t_data *data, int ac, char **av)
{
	if (ac == 2 && (ft_strncmp(av[1], "mandelbrot\0", 11) == 0))
	{
		data->type = MANDELBROT;
		return (1);
	}
	else if (ac == 4 && (ft_strncmp(av[1], "julia\0", 6) == 0))
	{
		if (!valid_number(av[2]) || !valid_number(av[3]))
			return (0);
		data->type = JULIA;
		data->julia_c.r = ft_atod(av[2]);
		data->julia_c.i = ft_atod(av[3]);
		if (fabs(data->julia_c.r) > 40.0
			|| fabs(data->julia_c.i) > 40.0)
			return (0);
		return (1);
	}
	else if (ac == 2 && (ft_strncmp(av[1], "burningship\0", 12) == 0))
	{
		data->type = BURNSHIP;
		return (1);
	}
	return (0);
}

int	valid_number(char *s)
{
	int	i;
	int	before;
	int	after;

	i = 0;
	before = 0;
	after = 0;
	if (!s || !s[0])
		return (0);
	if (is_sign(s[i]))
		i++;
	while (ft_isdigit(s[i]) && ++before)
		i++;
	if (s[i] == '.')
	{
		i++;
		while (ft_isdigit(s[i]) && ++after)
			i++;
	}
	if (!before || (i > 0 && s[i - 1] == '.' && !after) || s[i])
		return (0);
	return (1);
}

int	is_sign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}
