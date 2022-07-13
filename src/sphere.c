/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:23:18 by bteak             #+#    #+#             */
/*   Updated: 2022/01/18 22:02:22 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sphere	*sphere_create(t_vec3 center, float radius)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = center;
	sphere->radius = radius;
	return (sphere);
}

t_vec3	sphere_get_normal(t_vec3 point, t_sphere sphere)
{
	t_vec3	n;

	n = vec3_substract(point, sphere.center);
	vec3_normalize(&n);
	return (n);
}

int	sphere_intersect(t_ray ray, t_sphere sphere, double *t)
{
	t_vec3	l;
	float	a;
	float	b;
	float	d;
	float	t1;

	l = vec3_substract(sphere.center, ray.origin);
	a = vec3_dot_product(l, ray.direction);
	d = vec3_dot_product(l, l) - a * a;
	if (d > sphere.radius * sphere.radius)
		return (0);
	b = sqrtf(sphere.radius * sphere.radius - d);
	*t = a - b;
	t1 = a + b;
	if (*t < 0)
		*t = t1;
	if (*t < 0)
		return (0);
	return (1);
}

void	sphere_filling(char *buff, t_scene *scene, t_val_error temp)
{
	t_sphere	*sphere;
	t_object	*object;
	t_material	albedo;
	char		**tokens;
	t_temp_obj	ts;

	tokens = ft_split(buff, ' ');
	count_tokens(5, temp, scene, tokens);
	ts.center = obj_coord_fill(temp, scene, tokens, 1);
	ts.radius = obj_single_fill(temp, scene, tokens, 2) / 2;
	ts.color = obj_color_fill(temp, scene, tokens, 3);
	albedo = obj_albedo_fill(temp, scene, tokens, 4);
	sphere = sphere_create(ts.center, ts.radius);
	object = object_create(sphere, SPHERE, ts.color, albedo);
	object_add_or_create(object, scene, tokens);
	free_tokens(tokens);
}
