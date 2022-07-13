/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:08:02 by bteak             #+#    #+#             */
/*   Updated: 2022/01/18 22:33:02 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	camera_up(t_vec3 cam_vec)
{
	t_vec3	vec;

	if ((cam_vec.x == 0 || cam_vec.x == 0)
		&& (cam_vec.z == 0 || cam_vec.z == 0))
	{
		if (cam_vec.y == -1)
			vec = vec3_create(0, 0, -1);
		if (cam_vec.y == 1)
			vec = vec3_create(0, 0, 1);
	}
	else
		vec = vec3_create(0, 1, 0);
	return (vec);
}

t_vec3	multiply_by_matrix(t_vec3 p, t_matrix m)
{
	t_vec3	res;

	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
	return (res);
}

t_matrix	look_at(t_vec3 origin, t_vec3 cam_vector)
{
	t_matrix	m;
	t_vec3		or;
	t_vec3		right;
	t_vec3		up;

	or = camera_up(cam_vector);
	vec3_normalize(&or);
	right = vec3_cross_product(or, cam_vector);
	vec3_normalize(&right);
	up = vec3_cross_product(cam_vector, right);
	vec3_normalize(&up);
	m.d[0][0] = right.x;
	m.d[0][1] = right.y;
	m.d[0][2] = right.z;
	m.d[1][0] = up.x;
	m.d[1][1] = up.y;
	m.d[1][2] = up.z;
	m.d[2][0] = cam_vector.x;
	m.d[2][1] = cam_vector.y;
	m.d[2][2] = cam_vector.z;
	m.d[3][0] = origin.x;
	m.d[3][1] = origin.y;
	m.d[3][2] = origin.z;
	return (m);
}
