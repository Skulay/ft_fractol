/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:29:34 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/03 07:52:14 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	parse_args(t_data *data, int ac, char **av)
{
	if (ac == 2 && (ft_strncmp(av[1], "mandelbrot", 10) == 0))
		data->type = MANDELBROT;
	else if (ac == 4 && (ft_strncmp(av[1], "julia", 5) == 0))
	{
		data->type = JULIA;
		data->julia_c.r = ft_atod(av[2]);
		data->julia_c.i = ft_atod(av[3]);
	}
	else if (ac == 2 && (ft_strncmp(av[1], "burningship", 11) == 0))
		data->type = BURNSHIP;
	else
		ft_how_to_use();
}
