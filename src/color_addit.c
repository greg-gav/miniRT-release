/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_addit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:30:11 by cowen             #+#    #+#             */
/*   Updated: 2022/01/16 17:45:09 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	color_r_to_int(t_color_r c)
{
	int		result;
	t_color	tmp;

	tmp.r = c.r * 256;
	tmp.g = c.g * 256;
	tmp.b = c.b * 256;
	tmp.t = c.a * 256;
	result = color_to_int(tmp);
	return (result);
}

t_color_r	color_r_multiply(t_color_r a, t_color_r b)
{
	t_color_r	result;

	result.r = fmin(a.r * b.r, 0.99);
	result.g = fmin(a.g * b.g, 0.99);
	result.b = fmin(a.b * b.b, 0.99);
	result.a = fmin(a.a * b.a, 0.99);
	return (result);
}

t_color_r	color_r_multiply_val(t_color_r c, float value)
{
	t_color_r	result;

	result.r = fmin(c.r * value, 0.999);
	result.g = fmin(c.g * value, 0.999);
	result.b = fmin(c.b * value, 0.999);
	result.a = fmin(c.a * value, 0.999);
	return (result);
}

t_color_r	color_r_add(t_color_r a, t_color_r b)
{
	t_color_r	result;

	result.r = fmin(a.r + b.r, 0.99);
	result.g = fmin(a.g + b.g, 0.99);
	result.b = fmin(a.b + b.b, 0.99);
	result.a = fmin(a.a + b.a, 0.99);
	return (result);
}

t_color_r	color_r_substract(t_color_r a, t_color_r b)
{
	t_color_r	result;

	result.r = fmax(a.r - b.r, 0.0);
	result.g = fmax(a.g - b.g, 0.0);
	result.b = fmax(a.b - b.b, 0.0);
	result.a = fmax(a.a - b.a, 0.0);
	return (result);
}
