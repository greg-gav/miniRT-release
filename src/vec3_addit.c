/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_addit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:27:10 by cowen             #+#    #+#             */
/*   Updated: 2022/01/17 00:47:59 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	vec3_len(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float	vec3_len2(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec3_dist(t_vec3 vec1, t_vec3 vec2)
{
	return (sqrt(pow(vec2.x - vec1.x, 2)
			+ pow(vec2.y - vec1.y, 2)
			+ pow(vec2.z - vec1.z, 2)));
}

void	vec3_normalize(t_vec3 *v)
{
	double	len;

	len = vec3_len(*v);
	if (len > 0)
	{
		v->x /= len;
		v->y /= len;
		v->z /= len;
	}
}

float	vec3_dot_product(t_vec3 a, t_vec3 b)
{
	float	result;

	result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (result);
}
