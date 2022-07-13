/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:08:04 by bteak             #+#    #+#             */
/*   Updated: 2022/01/19 21:27:33 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_vec3	ray_reflect(t_vec3 dir, t_vec3 normal)
{
	float	dot;
	t_vec3	multi;

	dot = vec3_dot_product(dir, normal);
	multi = vec3_multiply(normal, 2.0 * dot);
	return (vec3_substract(dir, multi));
}

t_vec3	ray_refract(t_vec3 dir, t_vec3 normal, float eta_t, float eta_i)
{
	float	cosi;
	float	eta;
	float	k;

	cosi = -fmax(-1.0, fmin(1.0, vec3_dot_product(dir, normal)));
	if (cosi < 0)
		return (ray_refract(dir, vec3_multiply(normal, -1.0), eta_i, eta_t));
	eta = eta_i / eta_t;
	k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0)
		return (vec3_create(1, 0, 0));
	else
		return (vec3_add(vec3_multiply(dir, eta),
				vec3_multiply(normal, (eta * cosi - sqrtf(k)))));
}

t_vec3	ray_get_direction(int x, int y, t_camera *camera)
{
	double	fov_coeff;
	double	aspect_ratio;
	double	p_x;
	double	p_y;
	t_vec3	dir;

	fov_coeff = tan(camera->fov / 2 * M_PI / 180);
	aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	p_x = (2 * (x + 0.5) / (double)WINDOW_WIDTH - 1) * aspect_ratio * fov_coeff;
	p_y = (1 - 2 * (y + 0.5) / (double)WINDOW_HEIGHT) * fov_coeff;
	dir = vec3_create(p_x, p_y, -1);
	vec3_normalize(&dir);
	return (dir);
}

t_ray	ray_from_camera(int x, int y, t_camera *camera)
{
	t_matrix	view;
	t_vec3		origin;
	t_vec3		direction;

	view = look_at(camera->position, camera->orientation);
	origin = multiply_by_matrix(vec3_create(0, 0, 0), view);
	direction = ray_get_direction(x, y, camera);
	direction = multiply_by_matrix(direction, view);
	direction = vec3_substract(direction, origin);
	vec3_normalize(&direction);
	return (ray_create(origin, direction));
}
