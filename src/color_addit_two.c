/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_addit_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:33:57 by cowen             #+#    #+#             */
/*   Updated: 2022/01/19 15:42:54 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color_r	color_r_mix(t_color_r a, t_color_r b, float t)
{
	t_color_r	result;

	result.r = sqrt((1. - t) * a.r * a.r + t * b.r * b.r);
	result.g = sqrt((1. - t) * a.g * a.g + t * b.g * b.g);
	result.b = sqrt((1. - t) * a.b * a.b + t * b.b * b.b);
	result.a = sqrt((1. - t) * a.a * a.a + t * b.a * b.a);
	return (result);
}

t_color_r	checkerboard2(t_hit *hit_info)
{
	int		add;

	add = floor(hit_info->hit.x + 1e-8)
		+ floor(hit_info->hit.y + 1e-8)
		+ floor(hit_info->hit.z + 1e-8);
	if (add % 2)
		return (from_int_to_r(COLOR_WHITE));
	return (from_int_to_r(0));
}
