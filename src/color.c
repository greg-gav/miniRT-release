/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:59:56 by bteak             #+#    #+#             */
/*   Updated: 2022/01/16 17:46:20 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	int_to_color(int color)
{
	t_color	new;

	new.t = (color & (0xFF << 24)) >> 24;
	new.r = (color & (0xFF << 16)) >> 16;
	new.g = (color & (0xFF << 8)) >> 8;
	new.b = color & 0xFF;
	return (new);
}

int	color_to_int(t_color c)
{
	int	result;

	result = (c.t << 24);
	result = result | (c.r << 16);
	result = result | (c.g << 8);
	result = result | (c.b);
	return (result);
}

t_color_r	from_color_to_r(t_color c)
{
	t_color_r	result;

	result.r = c.r / 255.;
	result.g = c.g / 255.;
	result.b = c.b / 255.;
	result.a = c.t / 255.;
	return (result);
}

t_color_r	from_int_to_r(int c)
{
	t_color		tmp;
	t_color_r	result;

	tmp = int_to_color(c);
	result.r = (float)tmp.r / 255;
	result.g = (float)tmp.g / 255;
	result.b = (float)tmp.b / 255;
	result.a = (float)tmp.t / 255;
	return (result);
}

t_color_r	color_r_light(t_color_r a, t_color_r b)
{
	t_color_r	result;

	result.r = fmax(a.r, b.r);
	result.g = fmax(a.g, b.g);
	result.r = fmax(a.b, b.b);
	result.a = fmax(a.a, b.a);
	return (result);
}
