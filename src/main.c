/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:06:30 by bteak             #+#    #+#             */
/*   Updated: 2022/01/19 21:30:12 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render(t_mlx *mlx, t_scene *scene)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray;

	printf("starting render\n");
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			ray = ray_from_camera(x, y, scene->camera);
			color = ray_cast(&ray, scene, 0);
			ft_mlx_pixel_put(mlx->image, x, y, color);
			++x;
		}
		++y;
	}
	printf("done render\n");
}

void	set_material(t_material material, t_object *object)
{
	const float	glossy[6] = {1.2, 0.9, 0.0, 0.0, 70.0, 1.0};
	const float	matte[6] = {1.2, 0.05, 0.0, 0.0, 10.0, 1.0};
	const float	glass[6] = {0.0, 0.5, 0.1, 0.8, 125.0, 1.5};
	const float	mirror[6] = {0.0, 10.0, 0.8, 0.0, 1425.0, 1.0};

	if (material == GLOSSY)
		ft_memcpy(object->albedo, glossy, sizeof(object->albedo));
	else if (material == GLASS)
	{
		ft_memcpy(object->albedo, glass, sizeof(object->albedo));
		object->color = from_int_to_r(COLOR_GLASS);
	}
	else if (material == MIRROR)
	{
		ft_memcpy(object->albedo, mirror, sizeof(object->albedo));
		object->color = from_int_to_r(COLOR_WHITE);
	}
	else
		ft_memcpy(object->albedo, matte, sizeof(object->albedo));
}

t_object	*object_create(void *obj, t_otype type, t_color_r color,
				t_material material)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	object->ptr = obj;
	object->type = type;
	object->color = color;
	object->checkerb = 0;
	if (material == CHECKERB)
		object->checkerb = 1;
	set_material(material, object);
	return (object);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_image	img;
	t_scene	scene;

	scene = (t_scene){};
	main_parse(argc, argv, &scene);
	if (!ft_init_mlx(&mlx))
		return (1);
	if (!ft_init_image(&img, &mlx))
		return (2);
	render(&mlx, &scene);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.image->img, 0, 0);
	mlx_destroy_image(mlx.mlx_ptr, mlx.image->img);
	free_structs(&scene, NULL);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
