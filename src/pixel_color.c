/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 00:29:46 by bteak             #+#    #+#             */
/*   Updated: 2022/01/20 15:34:34 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	apply_ambient(t_color_r *material, t_scene *scene)
{
	t_color_r	col_tmp;

	col_tmp = from_color_to_r(scene->ambient->color);
	*material = color_r_mix(*material, col_tmp, 0.5);
	*material = color_r_multiply_val(*material, scene->ambient->intensity * 2);
}

t_color_r	scale_col(t_color_r c)
{
	float		max;
	float		scale;
	t_color_r	result;

	max = fmax(c.r, fmax(c.g, c.b));
	scale = 1.0 / max;
	result.r = c.r * scale;
	result.g = c.g * scale;
	result.b = c.b * scale;
	return (result);
}

void	get_pixel_color(t_scene *scene, t_hit *hit_info,
			t_color_r *material, int lights_num)
{
	float		ds_light[2];
	t_color_r	ds_color[2];
	t_color_r	col_tmp;

	ft_memset(ds_light, 0, sizeof(ds_light));
	ft_memset(ds_color, 0, sizeof(ds_color));
	iterate_all_lights(scene, hit_info, ds_light, ds_color);
	*material = hit_info->hit_obj->color;
	if (hit_info->hit_obj->checkerb)
		*material = checkerboard2(hit_info);
	*material = color_r_multiply_val(*material, ds_light[0] / lights_num);
	*material = color_r_multiply_val(*material, hit_info->hit_obj->albedo[0]);
	col_tmp = color_r_add(scale_col(ds_color[0]), *material);
	col_tmp = color_r_multiply_val(col_tmp, ds_light[1]);
	col_tmp = color_r_multiply_val(col_tmp, hit_info->hit_obj->albedo[1]);
	*material = color_r_add(*material, col_tmp);
	col_tmp = color_r_multiply_val(from_int_to_r(hit_info->reflect_color),
			hit_info->hit_obj->albedo[2]);
	*material = color_r_add(*material, col_tmp);
	col_tmp = color_r_multiply_val(from_int_to_r(hit_info->refract_color),
			hit_info->hit_obj->albedo[3]);
	*material = color_r_add(*material, col_tmp);
	*material = color_r_mix(*material, ds_color[0], 0.5);
	apply_ambient(material, scene);
}

static void	light_color_add(t_light *light, t_hit *hit_info,
	float ds_light[2], t_color_r ds_color[2])
{
	t_vec3	light_dir;
	double	fac;

	light_dir = vec3_substract(light->position, hit_info->hit);
	vec3_normalize(&light_dir);
	fac = vec3_dot_product(light_dir, hit_info->hit_normal);
	ds_light[0] += light->intensity * fmax(0.0, fac);
	ds_light[1] += powf(fmax(0.0, vec3_dot_product(
					ray_reflect(light_dir, hit_info->hit_normal),
					hit_info->hit_ray.direction)),
			(hit_info->hit_obj->albedo[4]) / light->intensity);
	if (fac > 0)
	{
		fac *= light->intensity;
		fac /= sqrt(vec3_dist(light->position, hit_info->hit)) / 2;
		ds_color[0] = color_r_add(ds_color[0],
				color_r_multiply_val(light->color, fmin(fac, 1.)));
	}
}

void	iterate_all_lights(t_scene *scene, t_hit *hit_info,
	float ds_light[2], t_color_r ds_color[2])
{
	t_list	*tmp;

	tmp = *(scene->lights);
	while (tmp)
	{
		ds_color[1] = color_r_add(ds_color[1],
				((t_light *)(tmp->content))->color);
		if (is_in_shadow(*(scene->objects),
				(t_light *)(tmp->content), hit_info))
		{
			tmp = tmp->next;
			continue ;
		}
		light_color_add((t_light *)(tmp->content),
			hit_info, ds_light, ds_color);
		tmp = tmp->next;
	}
}
