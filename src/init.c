/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:39:39 by bteak             #+#    #+#             */
/*   Updated: 2022/01/13 18:51:58 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	if (!mlx->win_ptr)
		return (0);
	mlx_hook(mlx->win_ptr, 17, 0, crossclose, (void *)mlx);
	mlx_hook(mlx->win_ptr, 02, 1L << 0, esc_key, (void *)mlx);
	return (1);
}

int	ft_init_image(t_image *img, t_mlx *mlx)
{
	img->img = mlx_new_image(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img->img)
		return (0);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
			&(img->line_length), &(img->endian));
	if (!img->addr)
		return (0);
	mlx->image = img;
	return (1);
}
