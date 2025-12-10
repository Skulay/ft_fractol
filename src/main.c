/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 07:13:50 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/10 14:31:38 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	main(int ac, char **av)
{
	t_data	*fractol;

	fractol = ft_init_struct();
	if (!fractol)
		return (1);
	if (!parse_args(fractol, ac, av))
	{
		free(fractol);
		ft_how_to_use();
		return (1);
	}
	if (!ft_init(fractol))
		return (close_window(fractol), 1);
	if (!ft_new_window(fractol))
		return (close_window(fractol), 1);
	if (!ft_new_image(fractol))
		return (close_window(fractol), 1);
	ft_get_addr(fractol);
	ft_render(fractol);
	mlx_hook(fractol->win, 2, 1L << 0, key_handler, fractol);
	mlx_hook(fractol->win, 4, 1L << 2, mouse_handler, fractol);
	mlx_hook(fractol->win, 17, 0, handle_close, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
void	ft_how_to_use(void)
{
	ft_printf("Usage:\n  ./fractol mandelbrot\n");
	ft_printf("  ./fractol julia <real> <imag>\n  ./fractol burningship\n");
	ft_printf("Exemples:\n  ./fractol julia -0.8 0.156\n");
}
