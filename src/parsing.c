/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:29:34 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/10 12:46:22 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	parse_args(t_data *data, int ac, char **av)
{
	if (ac == 2 && (ft_strncmp(av[1], "mandelbrot", 10) == 0))
	{
		data->type = MANDELBROT;
		return (1);
	}
	else if (ac == 4 && (ft_strncmp(av[1], "julia", 5) == 0))
	{
		if (!verif_arg(av[2]) || !verif_arg(av[3]))
			return (ft_how_to_use(), 0);
		data->type = JULIA;
		data->julia_c.r = ft_atod(av[2]);
		data->julia_c.i = ft_atod(av[3]);
		return (1);
	}
	else if (ac == 2 && (ft_strncmp(av[1], "burningship", 11) == 0))
	{
		data->type = BURNSHIP;
		return (1);
	}
	else
		return (ft_how_to_use(), 0);
	return (0);
}

int	verif_arg(char *av)
{
	char	*str;
	int		i;
	int		j;
	int		ok;

	str = " +-0123456789.";
	i = 0;
	while (av[i])
	{
		j = 0;
		ok = 0;
		while (str[j])
		{
			if (str[j] == av[i])
			{
				ok = 1;
				break ;
			}
			j++;
		}
		if (!ok)
			return (0);
		i++;
	}
	return (1);
}

