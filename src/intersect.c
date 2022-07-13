/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:33:46 by bteak             #+#    #+#             */
/*   Updated: 2022/01/19 15:42:49 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	intersect_object(t_ray *ray, t_object *object, double *t)
{
	if (object->type == SPHERE)
		return (sphere_intersect(*ray, *(t_sphere *)object->ptr, t));
	else if (object->type == PLANE)
		return (plane_intersect(*ray, *(t_plane *)object->ptr, t));
	else if (object->type == CYLINDER)
		return (cylinder_intersect(*ray, *(t_cylinder *)object->ptr, t));
	else if (object->type == CONE)
		return (cone_intersect(*ray, *(t_cone *)object->ptr, t));
	else
		return (0);
}

t_vec3	get_object_normal(t_vec3 hit, t_object *object, t_hit *info)
{
	t_vec3	norm;

	norm = vec3_create(0, 0, 0);
	if (object->type == CYLINDER)
	{
		norm = get_cylinder_normal(hit, *(t_cylinder *)object->ptr);
		if (vec3_dot_product(info->hit_ray.direction, norm) > 0)
			norm = vec3_multiply(norm, -1.0);
	}
	else if (object->type == CONE)
	{
		norm = get_cone_normal(hit, *(t_cone *)object->ptr);
		if (vec3_dot_product(info->hit_ray.direction, norm) > 0)
			norm = vec3_multiply(norm, -1.0);
	}
	else if (object->type == SPHERE)
		norm = sphere_get_normal(hit, *(t_sphere *)object->ptr);
	if (object->type == PLANE)
	{
		norm = get_plane_normal(hit, *(t_plane *)object->ptr);
		if (vec3_dot_product(info->hit_ray.direction, norm) > 0)
			norm = vec3_multiply(norm, -1.0);
	}
	return (norm);
}

int	scene_intersect(t_list *objects, t_hit *info)
{
	t_list	*tmp;
	double	dist_i;
	double	object_dist;

	info->hit_obj = NULL;
	object_dist = DBL_MAX;
	tmp = objects;
	while (tmp)
	{
		dist_i = 0;
		if (intersect_object(&info->hit_ray, (t_object *)(tmp->content),
			&dist_i) && dist_i < object_dist)
		{
			object_dist = dist_i;
			info->hit = vec3_add(info->hit_ray.origin,
					vec3_multiply(info->hit_ray.direction, dist_i));
			info->hit_obj = (t_object *)tmp->content;
		}
		tmp = tmp->next;
	}
	return (object_dist < 1000);
}

int	is_in_shadow(t_list *objects, t_light *light, t_hit *info)
{
	t_vec3	shadow_orig;
	t_vec3	light_dir;
	float	light_distance;
	t_hit	shadow_hit;

	light_dir = vec3_substract(light->position, info->hit);
	vec3_normalize(&light_dir);
	light_distance = vec3_len(vec3_substract(light->position, info->hit));
	if (vec3_dot_product(light_dir, info->hit_normal) < 0)
		shadow_orig = (vec3_substract(info->hit,
					vec3_multiply(info->hit_normal, 1e-3)));
	else
		shadow_orig = (vec3_add(info->hit,
					vec3_multiply(info->hit_normal, 1e-3)));
	shadow_hit.hit_ray = ray_create(shadow_orig, light_dir);
	if (scene_intersect(objects, &shadow_hit)
		&& vec3_len(vec3_substract(shadow_hit.hit,
				shadow_orig)) < light_distance)
		return (1);
	return (0);
}
