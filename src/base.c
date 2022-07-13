/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:56:14 by bteak             #+#    #+#             */
/*   Updated: 2022/01/19 23:21:56 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_base(t_base *base, t_vec3 orient)
{
	t_vec3	u;

	u = vec3_create(0, 1, 0);
	base->z_axis = orient;
	if (fabs(orient.y) == 1)
		base->x_axis = vec3_create(0, 0, 1);
	else
		base->x_axis = vec3_cross_product(u, base->z_axis);
	base->y_axis = vec3_cross_product(base->z_axis, base->x_axis);
	vec3_normalize(&(base->x_axis));
	vec3_normalize(&(base->y_axis));
	vec3_normalize(&(base->z_axis));
}
