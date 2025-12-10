/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:13:50 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/10 12:51:16 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	main(int ac, char **av)
{
	t_data	*fractol;

	fractol = ft_init_struct();
	if (!fractol)
		exit(1);
	if (!parse_args(fractol, ac, av))
	{
		free(fractol);
		ft_how_to_use();
		exit(1);
	}
	if (!ft_init(fractol))
		exit(close_window(fractol));
	if (!ft_new_window(fractol))
		exit(close_window(fractol));
	if (!ft_new_image(fractol))
		exit(close_window(fractol));
	ft_get_addr(fractol);
	ft_render(fractol);
	mlx_hook(fractol->win, 2, 1L << 0, key_handler, fractol);
	mlx_hook(fractol->win, 4, 1L << 2, mouse_handler, fractol);
	mlx_hook(fractol->win, 17, 0, close_window, fractol);
	mlx_loop(fractol->mlx);
	exit(0);
}
