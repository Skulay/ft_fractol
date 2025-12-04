/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:13:50 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/04 13:37:59 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	main(int ac, char **av)
{
	t_data	*fractol;

	fractol = ft_init();
	if (!fractol)
		return (1);
	parse_args(fractol, ac, av);
	ft_new_window(fractol);
	ft_new_image(fractol);
	ft_get_addr(fractol);
	ft_render(fractol);
	mlx_hook(fractol->win, 2, 1L << 0, key_handler, fractol);
	mlx_hook(fractol->win, 4, 1L << 2, mouse_handler, fractol);
	mlx_hook(fractol->win, 17, 0, close_window, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
