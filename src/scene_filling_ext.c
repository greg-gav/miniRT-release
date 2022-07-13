/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_filling_ext.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:22:41 by cowen             #+#    #+#             */
/*   Updated: 2022/01/16 17:26:11 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color_r	obj_color_fill(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	t_color_r	color;
	char		*buff;

	buff = tmp.buff;
	tmp = parsing_color(tok[pos]);
	tmp.buff = buff;
	parse_error_msg(tmp.err_value, scene, &tmp, tok);
	color = from_int_to_r(tmp.colour);
	return (color);
}

t_material	obj_albedo_fill(t_val_error tmp, t_scene *scene, char **tok, int ps)
{
	int	value;

	if (tok[ps])
	{
		value = ft_atoi(tok[ps]);
		if (value == 1)
			return (GLOSSY);
		if (value == 2)
			return (MATTE);
		if (value == 3)
			return (GLASS);
		if (value == 4)
			return (MIRROR);
		if (value == 5)
			return (CHECKERB);
		parse_error_msg(ALB_ERROR, scene, &tmp, tok);
	}
	return (MATTE);
}

t_vec3	obj_orient_fill(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	t_vec3	orientation;
	char	*buff;

	buff = tmp.buff;
	tmp = ft_tripple_stof(tok[pos]);
	tmp.buff = buff;
	if (tmp.x_f < -1 || tmp.x_f > 1)
		parse_error_msg(ONE_VALUE, scene, &tmp, tok);
	if (tmp.y_f < -1 || tmp.y_f > 1)
		parse_error_msg(ONE_VALUE, scene, &tmp, tok);
	if (tmp.z_f < -1 || tmp.z_f > 1)
		parse_error_msg(ONE_VALUE, scene, &tmp, tok);
	parse_error_msg(tmp.err_value, scene, &tmp, tok);
	orientation = vec3_create(tmp.x_f, tmp.y_f, tmp.z_f);
	return (orientation);
}
