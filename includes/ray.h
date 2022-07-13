/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:09:24 by bteak             #+#    #+#             */
/*   Updated: 2022/01/18 22:51:02 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_scene
{
	t_list		**objects;
	t_list		**lights;
	t_camera	*camera;
	t_ambient	*ambient;
}				t_scene;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}				t_ray;

t_ray	ray_create(t_vec3 origin, t_vec3 direction);
t_vec3	ray_get_direction(int x, int y, t_camera *camera);
int		ray_cast(t_ray *ray, t_scene *scene, int bounce);
t_ray	ray_from_camera(int x, int y, t_camera *camera);
t_vec3	ray_reflect(t_vec3 dir, t_vec3 normal);
t_vec3	ray_refract(t_vec3 dir, t_vec3 normal, float eta_t, float eta_i);
t_vec3	ray_get_direction(int x, int y, t_camera *camera);
t_ray	ray_from_camera(int x, int y, t_camera *camera);

#endif